/*
 * EHCI HCD (Host Controller Driver) for USB.
 *
 * Bus Glue for AMD Alchemy Au1xxx
 *
 * Based on "ohci-au1xxx.c" by Matt Porter <mporter@kernel.crashing.org>
 *
 * Modified for AMD Alchemy Au1200 EHC
 *  by K.Boge <karsten.boge@amd.com>
 *
 * This file is licenced under the GPL.
 */

#include <linux/platform_device.h>
#include <asm/mach-au1x00/au1000.h>


extern int usb_disabled(void);

static int au1xxx_ehci_setup(struct usb_hcd *hcd)
{
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	int ret = ehci_init(hcd);

	ehci->need_io_watchdog = 0;
	ehci_reset(ehci);
	return ret;
}

static const struct hc_driver ehci_au1xxx_hc_driver = {
	.description		= hcd_name,
	.product_desc		= "Au1xxx EHCI",
	.hcd_priv_size		= sizeof(struct ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq			= ehci_irq,
	.flags			= HCD_MEMORY | HCD_USB2,

	/*
	 * basic lifecycle operations
	 *
	 * FIXME -- ehci_init() doesn't do enough here.
	 * See ehci-ppc-soc for a complete implementation.
	 */
	.reset			= au1xxx_ehci_setup,
	.start			= ehci_run,
	.stop			= ehci_stop,
	.shutdown		= ehci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue		= ehci_urb_enqueue,
	.urb_dequeue		= ehci_urb_dequeue,
	.endpoint_disable	= ehci_endpoint_disable,
	.endpoint_reset		= ehci_endpoint_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number	= ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data	= ehci_hub_status_data,
	.hub_control		= ehci_hub_control,
	.bus_suspend		= ehci_bus_suspend,
	.bus_resume		= ehci_bus_resume,
	.relinquish_port	= ehci_relinquish_port,
	.port_handed_over	= ehci_port_handed_over,

	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
};

static int ehci_hcd_au1xxx_drv_probe(struct platform_device *pdev)
{
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;
	struct resource *res;
	int ret;

	if (usb_disabled())
		return -ENODEV;

	if (pdev->resource[1].flags != IORESOURCE_IRQ) {
		pr_debug("resource[1] is not IORESOURCE_IRQ");
		return -ENOMEM;
	}
	hcd = usb_create_hcd(&ehci_au1xxx_hc_driver, &pdev->dev, "Au1xxx");
	if (!hcd)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		pr_debug("request_mem_region failed");
		ret = -EBUSY;
		goto err1;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		pr_debug("ioremap failed");
		ret = -ENOMEM;
		goto err2;
	}

	if (alchemy_usb_control(ALCHEMY_USB_EHCI0, 1)) {
		printk(KERN_INFO "%s: controller init failed!\n", pdev->name);
		ret = -ENODEV;
		goto err3;
	}

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs;
	ehci->regs = hcd->regs +
		HC_LENGTH(ehci, readl(&ehci->caps->hc_capbase));
	/* cache this readonly data; minimize chip reads */
	ehci->hcs_params = readl(&ehci->caps->hcs_params);

	ret = usb_add_hcd(hcd, pdev->resource[1].start,
			  IRQF_SHARED);
	if (ret == 0) {
		platform_set_drvdata(pdev, hcd);
		return ret;
	}

	alchemy_usb_control(ALCHEMY_USB_EHCI0, 0);
err3:
	iounmap(hcd->regs);
err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err1:
	usb_put_hcd(hcd);
	return ret;
}

static int ehci_hcd_au1xxx_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_remove_hcd(hcd);
	alchemy_usb_control(ALCHEMY_USB_EHCI0, 0);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

#ifdef CONFIG_PM
static int ehci_hcd_au1xxx_drv_suspend(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);
	unsigned long flags;
	int rc = 0;

	if (time_before(jiffies, ehci->next_statechange))
		msleep(10);

	/* Root hub was already suspended. Disable irq emission and
	 * mark HW unaccessible.  The PM and USB cores make sure that
	 * the root hub is either suspended or stopped.
	 */
	ehci_prepare_ports_for_controller_suspend(ehci, device_may_wakeup(dev));
	spin_lock_irqsave(&ehci->lock, flags);
	ehci_writel(ehci, 0, &ehci->regs->intr_enable);
	(void)ehci_readl(ehci, &ehci->regs->intr_enable);

	clear_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);
	spin_unlock_irqrestore(&ehci->lock, flags);

	// could save FLADJ in case of Vaux power loss
	// ... we'd only use it to handle clock skew

	alchemy_usb_control(ALCHEMY_USB_EHCI0, 0);

	return rc;
}

static int ehci_hcd_au1xxx_drv_resume(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct ehci_hcd *ehci = hcd_to_ehci(hcd);

	alchemy_usb_control(ALCHEMY_USB_EHCI0, 1);

	// maybe restore FLADJ

	if (time_before(jiffies, ehci->next_statechange))
		msleep(100);

	/* Mark hardware accessible again as we are out of D3 state by now */
	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	/* If CF is still set, we maintained PCI Vaux power.
	 * Just undo the effect of ehci_pci_suspend().
	 */
	if (ehci_readl(ehci, &ehci->regs->configured_flag) == FLAG_CF) {
		int	mask = INTR_MASK;

		ehci_prepare_ports_for_controller_resume(ehci);
		if (!hcd->self.root_hub->do_remote_wakeup)
			mask &= ~STS_PCD;
		ehci_writel(ehci, mask, &ehci->regs->intr_enable);
		ehci_readl(ehci, &ehci->regs->intr_enable);
		return 0;
	}

	ehci_dbg(ehci, "lost power, restarting\n");
	usb_root_hub_lost_power(hcd->self.root_hub);

	/* Else reset, to cope with power loss or flush-to-storage
	 * style "resume" having let BIOS kick in during reboot.
	 */
	(void) ehci_halt(ehci);
	(void) ehci_reset(ehci);

	/* emptying the schedule aborts any urbs */
	spin_lock_irq(&ehci->lock);
	if (ehci->reclaim)
		end_unlink_async(ehci);
	ehci_work(ehci);
	spin_unlock_irq(&ehci->lock);

	ehci_writel(ehci, ehci->command, &ehci->regs->command);
	ehci_writel(ehci, FLAG_CF, &ehci->regs->configured_flag);
	ehci_readl(ehci, &ehci->regs->command);	/* unblock posted writes */

	/* here we "know" root ports should always stay powered */
	ehci_port_power(ehci, 1);

	ehci->rh_state = EHCI_RH_SUSPENDED;

	return 0;
}

static const struct dev_pm_ops au1xxx_ehci_pmops = {
	.suspend	= ehci_hcd_au1xxx_drv_suspend,
	.resume		= ehci_hcd_au1xxx_drv_resume,
};

#define AU1XXX_EHCI_PMOPS &au1xxx_ehci_pmops

#else
#define AU1XXX_EHCI_PMOPS NULL
#endif

static struct platform_driver ehci_hcd_au1xxx_driver = {
	.probe		= ehci_hcd_au1xxx_drv_probe,
	.remove		= ehci_hcd_au1xxx_drv_remove,
	.shutdown	= usb_hcd_platform_shutdown,
	.driver = {
		.name	= "au1xxx-ehci",
		.owner	= THIS_MODULE,
		.pm	= AU1XXX_EHCI_PMOPS,
	}
};

MODULE_ALIAS("platform:au1xxx-ehci");
