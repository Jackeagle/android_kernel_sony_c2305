#
# Makefile for nfc devices
#

obj-$(CONFIG_PN544_NFC)		+= pn544.o
obj-$(CONFIG_NFC_PN533)		+= pn533.o
obj-$(CONFIG_NFC_WILINK)	+= nfcwilink.o

# obj-$(CONFIG_NFC_MSR3110)  += msr3110.o
ccflags-$(CONFIG_NFC_DEBUG) := -DDEBUG
