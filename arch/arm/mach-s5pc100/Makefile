# arch/arm/mach-s5pc100/Makefile
#
# Copyright 2009 Samsung Electronics Co.
#
# Licensed under GPLv2

obj-y				:=
obj-m				:=
obj-n				:=
obj-				:=

# Core

obj-y				+= common.o clock.o

obj-y				+= dma.o

# machine support

obj-$(CONFIG_MACH_SMDKC100)	+= mach-smdkc100.o

# device support

obj-y				+= dev-audio.o

obj-y					+= setup-i2c0.o
obj-$(CONFIG_S5PC100_SETUP_FB_24BPP)	+= setup-fb-24bpp.o
obj-$(CONFIG_S5PC100_SETUP_I2C1)	+= setup-i2c1.o
obj-$(CONFIG_S5PC100_SETUP_IDE)		+= setup-ide.o
obj-$(CONFIG_S5PC100_SETUP_KEYPAD)	+= setup-keypad.o
obj-$(CONFIG_S5PC100_SETUP_SDHCI_GPIO)	+= setup-sdhci-gpio.o
obj-$(CONFIG_S5PC100_SETUP_SPI)		+= setup-spi.o
