/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/platform_device.h>
#include <asm/mips-boards/simint.h>

#define MIPSNET_VERSION "2007-11-17"

/*
 * Net status/control block as seen by sw in the core.
 */
struct mipsnet_regs {
	/*
	 * Device info for probing, reads as MIPSNET%d where %d is some
	 * form of version.
	 */
	u64 devId;		/*0x00 */

	/*
	 * read only busy flag.
	 * Set and cleared by the Net Device to indicate that an rx or a tx
	 * is in progress.
	 */
	u32 busy;		/*0x08 */

	/*
	 * Set by the Net Device.
	 * The device will set it once data has been received.
	 * The value is the number of bytes that should be read from
	 * rxDataBuffer.  The value will decrease till 0 until all the data
	 * from rxDataBuffer has been read.
	 */
	u32 rxDataCount;	/*0x0c */
#define MIPSNET_MAX_RXTX_DATACOUNT (1 << 16)

	/*
	 * Settable from the MIPS core, cleared by the Net Device.
	 * The core should set the number of bytes it wants to send,
	 * then it should write those bytes of data to txDataBuffer.
	 * The device will clear txDataCount has been processed (not
	 * necessarily sent).
	 */
	u32 txDataCount;	/*0x10 */

	/*
	 * Interrupt control
	 *
	 * Used to clear the interrupted generated by this dev.
	 * Write a 1 to clear the interrupt. (except bit31).
	 *
	 * Bit0 is set if it was a tx-done interrupt.
	 * Bit1 is set when new rx-data is available.
	 *    Until this bit is cleared there will be no other RXs.
	 *
	 * Bit31 is used for testing, it clears after a read.
	 *    Writing 1 to this bit will cause an interrupt to be generated.
	 *    To clear the test interrupt, write 0 to this register.
	 */
	u32 interruptControl;	/*0x14 */
#define MIPSNET_INTCTL_TXDONE     (1u << 0)
#define MIPSNET_INTCTL_RXDONE     (1u << 1)
#define MIPSNET_INTCTL_TESTBIT    (1u << 31)

	/*
	 * Readonly core-specific interrupt info for the device to signal
	 * the core. The meaning of the contents of this field might change.
	 */
	/* XXX: the whole memIntf interrupt scheme is messy: the device
	 * should have no control what so ever of what VPE/register set is
	 * being used.
	 * The MemIntf should only expose interrupt lines, and something in
	 * the config should be responsible for the line<->core/vpe bindings.
	 */
	u32 interruptInfo;	/*0x18 */

	/*
	 * This is where the received data is read out.
	 * There is more data to read until rxDataReady is 0.
	 * Only 1 byte at this regs offset is used.
	 */
	u32 rxDataBuffer;	/*0x1c */

	/*
	 * This is where the data to transmit is written.
	 * Data should be written for the amount specified in the
	 * txDataCount register.
	 * Only 1 byte at this regs offset is used.
	 */
	u32 txDataBuffer;	/*0x20 */
};

#define regaddr(dev, field) \
  (dev->base_addr + offsetof(struct mipsnet_regs, field))

static char mipsnet_string[] = "mipsnet";

/*
 * Copy data from the MIPSNET rx data port
 */
static int ioiocpy_frommipsnet(struct net_device *dev, unsigned char *kdata,
			int len)
{
	for (; len > 0; len--, kdata++)
		*kdata = inb(regaddr(dev, rxDataBuffer));

	return inl(regaddr(dev, rxDataCount));
}

static inline void mipsnet_put_todevice(struct net_device *dev,
	struct sk_buff *skb)
{
	int count_to_go = skb->len;
	char *buf_ptr = skb->data;

	outl(skb->len, regaddr(dev, txDataCount));

	for (; count_to_go; buf_ptr++, count_to_go--)
		outb(*buf_ptr, regaddr(dev, txDataBuffer));

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	dev_kfree_skb(skb);
}

static int mipsnet_xmit(struct sk_buff *skb, struct net_device *dev)
{
	/*
	 * Only one packet at a time. Once TXDONE interrupt is serviced, the
	 * queue will be restarted.
	 */
	netif_stop_queue(dev);
	mipsnet_put_todevice(dev, skb);

	return NETDEV_TX_OK;
}

static inline ssize_t mipsnet_get_fromdev(struct net_device *dev, size_t len)
{
	struct sk_buff *skb;

	if (!len)
		return len;

	skb = netdev_alloc_skb(dev, len + NET_IP_ALIGN);
	if (!skb) {
		dev->stats.rx_dropped++;
		return -ENOMEM;
	}

	skb_reserve(skb, NET_IP_ALIGN);
	if (ioiocpy_frommipsnet(dev, skb_put(skb, len), len))
		return -EFAULT;

	skb->protocol = eth_type_trans(skb, dev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	netif_rx(skb);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	return len;
}

static irqreturn_t mipsnet_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	u32 int_flags;
	irqreturn_t ret = IRQ_NONE;

	if (irq != dev->irq)
		goto out_badirq;

	/* TESTBIT is cleared on read. */
	int_flags = inl(regaddr(dev, interruptControl));
	if (int_flags & MIPSNET_INTCTL_TESTBIT) {
		/* TESTBIT takes effect after a write with 0. */
		outl(0, regaddr(dev, interruptControl));
		ret = IRQ_HANDLED;
	} else if (int_flags & MIPSNET_INTCTL_TXDONE) {
		/* Only one packet at a time, we are done. */
		dev->stats.tx_packets++;
		netif_wake_queue(dev);
		outl(MIPSNET_INTCTL_TXDONE,
		     regaddr(dev, interruptControl));
		ret = IRQ_HANDLED;
	} else if (int_flags & MIPSNET_INTCTL_RXDONE) {
		mipsnet_get_fromdev(dev, inl(regaddr(dev, rxDataCount)));
		outl(MIPSNET_INTCTL_RXDONE, regaddr(dev, interruptControl));
		ret = IRQ_HANDLED;
	}
	return ret;

out_badirq:
	printk(KERN_INFO "%s: %s(): irq %d for unknown device\n",
	       dev->name, __func__, irq);
	return ret;
}

static int mipsnet_open(struct net_device *dev)
{
	int err;

	err = request_irq(dev->irq, mipsnet_interrupt,
			  IRQF_SHARED, dev->name, (void *) dev);
	if (err) {
		release_region(dev->base_addr, sizeof(struct mipsnet_regs));
		return err;
	}

	netif_start_queue(dev);

	/* test interrupt handler */
	outl(MIPSNET_INTCTL_TESTBIT, regaddr(dev, interruptControl));

	return 0;
}

static int mipsnet_close(struct net_device *dev)
{
	netif_stop_queue(dev);
	free_irq(dev->irq, dev);
	return 0;
}

static void mipsnet_set_mclist(struct net_device *dev)
{
}

static const struct net_device_ops mipsnet_netdev_ops = {
	.ndo_open		= mipsnet_open,
	.ndo_stop		= mipsnet_close,
	.ndo_start_xmit		= mipsnet_xmit,
	.ndo_set_rx_mode	= mipsnet_set_mclist,
	.ndo_change_mtu		= eth_change_mtu,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_set_mac_address	= eth_mac_addr,
};

static int __devinit mipsnet_probe(struct platform_device *dev)
{
	struct net_device *netdev;
	int err;

	netdev = alloc_etherdev(0);
	if (!netdev) {
		err = -ENOMEM;
		goto out;
	}

	platform_set_drvdata(dev, netdev);

	netdev->netdev_ops = &mipsnet_netdev_ops;

	/*
	 * TODO: probe for these or load them from PARAM
	 */
	netdev->base_addr = 0x4200;
	netdev->irq = MIPS_CPU_IRQ_BASE + MIPSCPU_INT_MB0 +
		      inl(regaddr(netdev, interruptInfo));

	/* Get the io region now, get irq on open() */
	if (!request_region(netdev->base_addr, sizeof(struct mipsnet_regs),
			    "mipsnet")) {
		err = -EBUSY;
		goto out_free_netdev;
	}

	/*
	 * Lacking any better mechanism to allocate a MAC address we use a
	 * random one ...
	 */
	eth_hw_addr_random(netdev);

	err = register_netdev(netdev);
	if (err) {
		printk(KERN_ERR "MIPSNet: failed to register netdev.\n");
		goto out_free_region;
	}

	return 0;

out_free_region:
	release_region(netdev->base_addr, sizeof(struct mipsnet_regs));

out_free_netdev:
	free_netdev(netdev);

out:
	return err;
}

static int __devexit mipsnet_device_remove(struct platform_device *device)
{
	struct net_device *dev = platform_get_drvdata(device);

	unregister_netdev(dev);
	release_region(dev->base_addr, sizeof(struct mipsnet_regs));
	free_netdev(dev);
	platform_set_drvdata(device, NULL);

	return 0;
}

static struct platform_driver mipsnet_driver = {
	.driver = {
		.name		= mipsnet_string,
		.owner		= THIS_MODULE,
	},
	.probe		= mipsnet_probe,
	.remove		= __devexit_p(mipsnet_device_remove),
};

static int __init mipsnet_init_module(void)
{
	int err;

	printk(KERN_INFO "MIPSNet Ethernet driver. Version: %s. "
	       "(c)2005 MIPS Technologies, Inc.\n", MIPSNET_VERSION);

	err = platform_driver_register(&mipsnet_driver);
	if (err)
		printk(KERN_ERR "Driver registration failed\n");

	return err;
}

static void __exit mipsnet_exit_module(void)
{
	platform_driver_unregister(&mipsnet_driver);
}

module_init(mipsnet_init_module);
module_exit(mipsnet_exit_module);
