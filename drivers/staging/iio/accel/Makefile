#
# Makefile for industrial I/O accelerometer drivers
#

adis16201-y             := adis16201_core.o
adis16201-$(CONFIG_IIO_BUFFER) += adis16201_ring.o adis16201_trigger.o
obj-$(CONFIG_ADIS16201) += adis16201.o

adis16203-y             := adis16203_core.o
adis16203-$(CONFIG_IIO_BUFFER) += adis16203_ring.o adis16203_trigger.o
obj-$(CONFIG_ADIS16203) += adis16203.o

adis16204-y             := adis16204_core.o
adis16204-$(CONFIG_IIO_BUFFER) += adis16204_ring.o adis16204_trigger.o
obj-$(CONFIG_ADIS16204) += adis16204.o

adis16209-y             := adis16209_core.o
adis16209-$(CONFIG_IIO_BUFFER) += adis16209_ring.o adis16209_trigger.o
obj-$(CONFIG_ADIS16209) += adis16209.o

adis16220-y             := adis16220_core.o
obj-$(CONFIG_ADIS16220) += adis16220.o

adis16240-y             := adis16240_core.o
adis16240-$(CONFIG_IIO_BUFFER) += adis16240_ring.o adis16240_trigger.o
obj-$(CONFIG_ADIS16240) += adis16240.o

obj-$(CONFIG_KXSD9)	+= kxsd9.o

lis3l02dq-y		:= lis3l02dq_core.o
lis3l02dq-$(CONFIG_IIO_BUFFER) += lis3l02dq_ring.o
obj-$(CONFIG_LIS3L02DQ)	+= lis3l02dq.o

sca3000-y		:= sca3000_core.o sca3000_ring.o
obj-$(CONFIG_SCA3000)	+= sca3000.o
