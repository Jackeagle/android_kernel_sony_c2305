#
# Makefile fragment for Broadcom 802.11n Networking Device Driver Utilities
#
# Copyright (c) 2011 Broadcom Corporation
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
# OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

ccflags-y :=				\
	-Idrivers/net/wireless/brcm80211/brcmutil \
	-Idrivers/net/wireless/brcm80211/include

BRCMUTIL_OFILES := \
	utils.o

MODULEPFX := brcmutil

obj-$(CONFIG_BRCMUTIL)	+= $(MODULEPFX).o
$(MODULEPFX)-objs	= $(BRCMUTIL_OFILES)
