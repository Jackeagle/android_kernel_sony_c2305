#
# Makefile for the m68knommu kernel.
#

#
# If you want to play with the HW breakpoints then you will
# need to add define this,  which will give you a stack backtrace
# on the console port whenever a DBG interrupt occurs. You have to
# set up you HW breakpoints to trigger a DBG interrupt:
#
# ccflags-y := -DTRAP_DBG_INTERRUPT
# asflags-y := -DTRAP_DBG_INTERRUPT
#

asflags-$(CONFIG_FULLDEBUG) := -DDEBUGGER_COMPATIBLE_CACHE=1

obj-$(CONFIG_COLDFIRE)	+= cache.o clk.o device.o dma.o entry.o vectors.o
obj-$(CONFIG_M5206)	+= timers.o intc.o reset.o
obj-$(CONFIG_M5206e)	+= timers.o intc.o reset.o
obj-$(CONFIG_M520x)	+= pit.o intc-simr.o reset.o
obj-$(CONFIG_M523x)	+= pit.o dma_timer.o intc-2.o reset.o
obj-$(CONFIG_M5249)	+= timers.o intc.o reset.o
obj-$(CONFIG_M527x)	+= pit.o intc-2.o reset.o
obj-$(CONFIG_M5272)	+= timers.o
obj-$(CONFIG_M528x)	+= pit.o intc-2.o reset.o
obj-$(CONFIG_M5307)	+= timers.o intc.o reset.o
obj-$(CONFIG_M532x)	+= timers.o intc-simr.o reset.o
obj-$(CONFIG_M5407)	+= timers.o intc.o reset.o
obj-$(CONFIG_M54xx)	+= sltimers.o intc-2.o

obj-y			+= pinmux.o gpio.o
extra-y := head.o
