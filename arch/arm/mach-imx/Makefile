obj-$(CONFIG_SOC_IMX1) += clock-imx1.o mm-imx1.o
obj-$(CONFIG_SOC_IMX21) += clock-imx21.o mm-imx21.o

obj-$(CONFIG_SOC_IMX25) += clock-imx25.o mm-imx25.o ehci-imx25.o cpu-imx25.o

obj-$(CONFIG_SOC_IMX27) += cpu-imx27.o pm-imx27.o
obj-$(CONFIG_SOC_IMX27) += clock-imx27.o mm-imx27.o ehci-imx27.o

obj-$(CONFIG_SOC_IMX31) += mm-imx3.o cpu-imx31.o clock-imx31.o iomux-imx31.o ehci-imx31.o pm-imx3.o
obj-$(CONFIG_SOC_IMX35) += mm-imx3.o cpu-imx35.o clock-imx35.o ehci-imx35.o pm-imx3.o

obj-$(CONFIG_SOC_IMX5) += cpu-imx5.o mm-imx5.o clock-mx51-mx53.o ehci-imx5.o pm-imx5.o cpu_op-mx51.o

# Support for CMOS sensor interface
obj-$(CONFIG_MX1_VIDEO) += mx1-camera-fiq.o mx1-camera-fiq-ksym.o

# i.MX1 based machines
obj-$(CONFIG_ARCH_MX1ADS) += mach-mx1ads.o
obj-$(CONFIG_MACH_SCB9328) += mach-scb9328.o
obj-$(CONFIG_MACH_APF9328) += mach-apf9328.o

# i.MX21 based machines
obj-$(CONFIG_MACH_MX21ADS) += mach-mx21ads.o

# i.MX25 based machines
obj-$(CONFIG_MACH_MX25_3DS) += mach-mx25_3ds.o
obj-$(CONFIG_MACH_EUKREA_CPUIMX25SD) += mach-eukrea_cpuimx25.o
obj-$(CONFIG_MACH_EUKREA_MBIMXSD25_BASEBOARD) += eukrea_mbimxsd25-baseboard.o

# i.MX27 based machines
obj-$(CONFIG_MACH_MX27ADS) += mach-mx27ads.o
obj-$(CONFIG_MACH_PCM038) += mach-pcm038.o
obj-$(CONFIG_MACH_PCM970_BASEBOARD) += pcm970-baseboard.o
obj-$(CONFIG_MACH_MX27_3DS) += mach-mx27_3ds.o
obj-$(CONFIG_MACH_IMX27LITE) += mach-imx27lite.o
obj-$(CONFIG_MACH_IMX27_VISSTRIM_M10) += mach-imx27_visstrim_m10.o
obj-$(CONFIG_MACH_CPUIMX27) += mach-cpuimx27.o
obj-$(CONFIG_MACH_EUKREA_MBIMX27_BASEBOARD) += eukrea_mbimx27-baseboard.o
obj-$(CONFIG_MACH_PCA100) += mach-pca100.o
obj-$(CONFIG_MACH_MXT_TD60) += mach-mxt_td60.o
obj-$(CONFIG_MACH_IMX27IPCAM) += mach-imx27ipcam.o
obj-$(CONFIG_MACH_IMX27_DT) += imx27-dt.o

# i.MX31 based machines
obj-$(CONFIG_MACH_MX31ADS) += mach-mx31ads.o
obj-$(CONFIG_MACH_MX31LILLY) += mach-mx31lilly.o mx31lilly-db.o
obj-$(CONFIG_MACH_MX31LITE) += mach-mx31lite.o mx31lite-db.o
obj-$(CONFIG_MACH_PCM037) += mach-pcm037.o
obj-$(CONFIG_MACH_PCM037_EET) += mach-pcm037_eet.o
obj-$(CONFIG_MACH_MX31_3DS) += mach-mx31_3ds.o
obj-$(CONFIG_MACH_MX31MOBOARD) += mach-mx31moboard.o mx31moboard-devboard.o \
		mx31moboard-marxbot.o mx31moboard-smartbot.o
obj-$(CONFIG_MACH_QONG) += mach-qong.o
obj-$(CONFIG_MACH_ARMADILLO5X0) += mach-armadillo5x0.o
obj-$(CONFIG_MACH_KZM_ARM11_01) += mach-kzm_arm11_01.o
obj-$(CONFIG_MACH_BUG) += mach-bug.o

# i.MX35 based machines
obj-$(CONFIG_MACH_PCM043) += mach-pcm043.o
obj-$(CONFIG_MACH_MX35_3DS) += mach-mx35_3ds.o
obj-$(CONFIG_MACH_EUKREA_CPUIMX35SD) += mach-cpuimx35.o
obj-$(CONFIG_MACH_EUKREA_MBIMXSD35_BASEBOARD) += eukrea_mbimxsd35-baseboard.o
obj-$(CONFIG_MACH_VPR200) += mach-vpr200.o

obj-$(CONFIG_DEBUG_LL) += lluart.o
obj-$(CONFIG_HAVE_IMX_GPC) += gpc.o
obj-$(CONFIG_HAVE_IMX_MMDC) += mmdc.o
obj-$(CONFIG_HAVE_IMX_SRC) += src.o
obj-$(CONFIG_CPU_V7) += head-v7.o
AFLAGS_head-v7.o :=-Wa,-march=armv7-a
obj-$(CONFIG_SMP) += platsmp.o
obj-$(CONFIG_HOTPLUG_CPU) += hotplug.o
obj-$(CONFIG_SOC_IMX6Q) += clock-imx6q.o mach-imx6q.o

ifeq ($(CONFIG_PM),y)
obj-$(CONFIG_SOC_IMX6Q) += pm-imx6q.o
endif

# i.MX5 based machines
obj-$(CONFIG_MACH_MX51_BABBAGE) += mach-mx51_babbage.o
obj-$(CONFIG_MACH_MX51_3DS) += mach-mx51_3ds.o
obj-$(CONFIG_MACH_MX53_EVK) += mach-mx53_evk.o
obj-$(CONFIG_MACH_MX53_SMD) += mach-mx53_smd.o
obj-$(CONFIG_MACH_MX53_LOCO) += mach-mx53_loco.o
obj-$(CONFIG_MACH_MX53_ARD) += mach-mx53_ard.o
obj-$(CONFIG_MACH_EUKREA_CPUIMX51) += mach-cpuimx51.o
obj-$(CONFIG_MACH_EUKREA_MBIMX51_BASEBOARD) += eukrea_mbimx51-baseboard.o
obj-$(CONFIG_MACH_EUKREA_CPUIMX51SD) += mach-cpuimx51sd.o
obj-$(CONFIG_MACH_EUKREA_MBIMXSD51_BASEBOARD) += eukrea_mbimxsd-baseboard.o
obj-$(CONFIG_MX51_EFIKA_COMMON) += mx51_efika.o
obj-$(CONFIG_MACH_MX51_EFIKAMX) += mach-mx51_efikamx.o
obj-$(CONFIG_MACH_MX51_EFIKASB) += mach-mx51_efikasb.o
obj-$(CONFIG_MACH_MX50_RDP) += mach-mx50_rdp.o

obj-$(CONFIG_MACH_IMX51_DT) += imx51-dt.o
obj-$(CONFIG_MACH_IMX53_DT) += imx53-dt.o
