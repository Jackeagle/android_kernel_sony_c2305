#
# Makefile for the linux kernel, U300 machine.
#

obj-y		:= core.o clock.o timer.o
obj-m		:=
obj-n		:=
obj-		:=

obj-$(CONFIG_ARCH_U300)	          += u300.o
obj-$(CONFIG_SPI_PL022)           += spi.o
obj-$(CONFIG_MACH_U300_SPIDUMMY)  += dummyspichip.o
obj-$(CONFIG_I2C_STU300)          += i2c.o
obj-$(CONFIG_REGULATOR_AB3100)    += regulator.o
