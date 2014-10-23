/*
 * Copyright (c) 2008, 2009, 2010 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* This file is mechanically generated from RTL. Any hand-edits will be lost! */

#define QIB_6120_Revision_OFFS 0x0
#define QIB_6120_Revision_R_Simulator_LSB 0x3F
#define QIB_6120_Revision_R_Simulator_RMASK 0x1
#define QIB_6120_Revision_Reserved_LSB 0x28
#define QIB_6120_Revision_Reserved_RMASK 0x7FFFFF
#define QIB_6120_Revision_BoardID_LSB 0x20
#define QIB_6120_Revision_BoardID_RMASK 0xFF
#define QIB_6120_Revision_R_SW_LSB 0x18
#define QIB_6120_Revision_R_SW_RMASK 0xFF
#define QIB_6120_Revision_R_Arch_LSB 0x10
#define QIB_6120_Revision_R_Arch_RMASK 0xFF
#define QIB_6120_Revision_R_ChipRevMajor_LSB 0x8
#define QIB_6120_Revision_R_ChipRevMajor_RMASK 0xFF
#define QIB_6120_Revision_R_ChipRevMinor_LSB 0x0
#define QIB_6120_Revision_R_ChipRevMinor_RMASK 0xFF

#define QIB_6120_Control_OFFS 0x8
#define QIB_6120_Control_TxLatency_LSB 0x4
#define QIB_6120_Control_TxLatency_RMASK 0x1
#define QIB_6120_Control_PCIERetryBufDiagEn_LSB 0x3
#define QIB_6120_Control_PCIERetryBufDiagEn_RMASK 0x1
#define QIB_6120_Control_LinkEn_LSB 0x2
#define QIB_6120_Control_LinkEn_RMASK 0x1
#define QIB_6120_Control_FreezeMode_LSB 0x1
#define QIB_6120_Control_FreezeMode_RMASK 0x1
#define QIB_6120_Control_SyncReset_LSB 0x0
#define QIB_6120_Control_SyncReset_RMASK 0x1

#define QIB_6120_PageAlign_OFFS 0x10

#define QIB_6120_PortCnt_OFFS 0x18

#define QIB_6120_SendRegBase_OFFS 0x30

#define QIB_6120_UserRegBase_OFFS 0x38

#define QIB_6120_CntrRegBase_OFFS 0x40

#define QIB_6120_Scratch_OFFS 0x48
#define QIB_6120_Scratch_TopHalf_LSB 0x20
#define QIB_6120_Scratch_TopHalf_RMASK 0xFFFFFFFF
#define QIB_6120_Scratch_BottomHalf_LSB 0x0
#define QIB_6120_Scratch_BottomHalf_RMASK 0xFFFFFFFF

#define QIB_6120_IntBlocked_OFFS 0x60
#define QIB_6120_IntBlocked_ErrorIntBlocked_LSB 0x1F
#define QIB_6120_IntBlocked_ErrorIntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_PioSetIntBlocked_LSB 0x1E
#define QIB_6120_IntBlocked_PioSetIntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_PioBufAvailIntBlocked_LSB 0x1D
#define QIB_6120_IntBlocked_PioBufAvailIntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_assertGPIOIntBlocked_LSB 0x1C
#define QIB_6120_IntBlocked_assertGPIOIntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_Reserved_LSB 0xF
#define QIB_6120_IntBlocked_Reserved_RMASK 0x1FFF
#define QIB_6120_IntBlocked_RcvAvail4IntBlocked_LSB 0x10
#define QIB_6120_IntBlocked_RcvAvail4IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvAvail3IntBlocked_LSB 0xF
#define QIB_6120_IntBlocked_RcvAvail3IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvAvail2IntBlocked_LSB 0xE
#define QIB_6120_IntBlocked_RcvAvail2IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvAvail1IntBlocked_LSB 0xD
#define QIB_6120_IntBlocked_RcvAvail1IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvAvail0IntBlocked_LSB 0xC
#define QIB_6120_IntBlocked_RcvAvail0IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_Reserved1_LSB 0x5
#define QIB_6120_IntBlocked_Reserved1_RMASK 0x7F
#define QIB_6120_IntBlocked_RcvUrg4IntBlocked_LSB 0x4
#define QIB_6120_IntBlocked_RcvUrg4IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvUrg3IntBlocked_LSB 0x3
#define QIB_6120_IntBlocked_RcvUrg3IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvUrg2IntBlocked_LSB 0x2
#define QIB_6120_IntBlocked_RcvUrg2IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvUrg1IntBlocked_LSB 0x1
#define QIB_6120_IntBlocked_RcvUrg1IntBlocked_RMASK 0x1
#define QIB_6120_IntBlocked_RcvUrg0IntBlocked_LSB 0x0
#define QIB_6120_IntBlocked_RcvUrg0IntBlocked_RMASK 0x1

#define QIB_6120_IntMask_OFFS 0x68
#define QIB_6120_IntMask_ErrorIntMask_LSB 0x1F
#define QIB_6120_IntMask_ErrorIntMask_RMASK 0x1
#define QIB_6120_IntMask_PioSetIntMask_LSB 0x1E
#define QIB_6120_IntMask_PioSetIntMask_RMASK 0x1
#define QIB_6120_IntMask_PioBufAvailIntMask_LSB 0x1D
#define QIB_6120_IntMask_PioBufAvailIntMask_RMASK 0x1
#define QIB_6120_IntMask_assertGPIOIntMask_LSB 0x1C
#define QIB_6120_IntMask_assertGPIOIntMask_RMASK 0x1
#define QIB_6120_IntMask_Reserved_LSB 0x11
#define QIB_6120_IntMask_Reserved_RMASK 0x7FF
#define QIB_6120_IntMask_RcvAvail4IntMask_LSB 0x10
#define QIB_6120_IntMask_RcvAvail4IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvAvail3IntMask_LSB 0xF
#define QIB_6120_IntMask_RcvAvail3IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvAvail2IntMask_LSB 0xE
#define QIB_6120_IntMask_RcvAvail2IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvAvail1IntMask_LSB 0xD
#define QIB_6120_IntMask_RcvAvail1IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvAvail0IntMask_LSB 0xC
#define QIB_6120_IntMask_RcvAvail0IntMask_RMASK 0x1
#define QIB_6120_IntMask_Reserved1_LSB 0x5
#define QIB_6120_IntMask_Reserved1_RMASK 0x7F
#define QIB_6120_IntMask_RcvUrg4IntMask_LSB 0x4
#define QIB_6120_IntMask_RcvUrg4IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvUrg3IntMask_LSB 0x3
#define QIB_6120_IntMask_RcvUrg3IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvUrg2IntMask_LSB 0x2
#define QIB_6120_IntMask_RcvUrg2IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvUrg1IntMask_LSB 0x1
#define QIB_6120_IntMask_RcvUrg1IntMask_RMASK 0x1
#define QIB_6120_IntMask_RcvUrg0IntMask_LSB 0x0
#define QIB_6120_IntMask_RcvUrg0IntMask_RMASK 0x1

#define QIB_6120_IntStatus_OFFS 0x70
#define QIB_6120_IntStatus_Error_LSB 0x1F
#define QIB_6120_IntStatus_Error_RMASK 0x1
#define QIB_6120_IntStatus_PioSent_LSB 0x1E
#define QIB_6120_IntStatus_PioSent_RMASK 0x1
#define QIB_6120_IntStatus_PioBufAvail_LSB 0x1D
#define QIB_6120_IntStatus_PioBufAvail_RMASK 0x1
#define QIB_6120_IntStatus_assertGPIO_LSB 0x1C
#define QIB_6120_IntStatus_assertGPIO_RMASK 0x1
#define QIB_6120_IntStatus_Reserved_LSB 0xF
#define QIB_6120_IntStatus_Reserved_RMASK 0x1FFF
#define QIB_6120_IntStatus_RcvAvail4_LSB 0x10
#define QIB_6120_IntStatus_RcvAvail4_RMASK 0x1
#define QIB_6120_IntStatus_RcvAvail3_LSB 0xF
#define QIB_6120_IntStatus_RcvAvail3_RMASK 0x1
#define QIB_6120_IntStatus_RcvAvail2_LSB 0xE
#define QIB_6120_IntStatus_RcvAvail2_RMASK 0x1
#define QIB_6120_IntStatus_RcvAvail1_LSB 0xD
#define QIB_6120_IntStatus_RcvAvail1_RMASK 0x1
#define QIB_6120_IntStatus_RcvAvail0_LSB 0xC
#define QIB_6120_IntStatus_RcvAvail0_RMASK 0x1
#define QIB_6120_IntStatus_Reserved1_LSB 0x5
#define QIB_6120_IntStatus_Reserved1_RMASK 0x7F
#define QIB_6120_IntStatus_RcvUrg4_LSB 0x4
#define QIB_6120_IntStatus_RcvUrg4_RMASK 0x1
#define QIB_6120_IntStatus_RcvUrg3_LSB 0x3
#define QIB_6120_IntStatus_RcvUrg3_RMASK 0x1
#define QIB_6120_IntStatus_RcvUrg2_LSB 0x2
#define QIB_6120_IntStatus_RcvUrg2_RMASK 0x1
#define QIB_6120_IntStatus_RcvUrg1_LSB 0x1
#define QIB_6120_IntStatus_RcvUrg1_RMASK 0x1
#define QIB_6120_IntStatus_RcvUrg0_LSB 0x0
#define QIB_6120_IntStatus_RcvUrg0_RMASK 0x1

#define QIB_6120_IntClear_OFFS 0x78
#define QIB_6120_IntClear_ErrorIntClear_LSB 0x1F
#define QIB_6120_IntClear_ErrorIntClear_RMASK 0x1
#define QIB_6120_IntClear_PioSetIntClear_LSB 0x1E
#define QIB_6120_IntClear_PioSetIntClear_RMASK 0x1
#define QIB_6120_IntClear_PioBufAvailIntClear_LSB 0x1D
#define QIB_6120_IntClear_PioBufAvailIntClear_RMASK 0x1
#define QIB_6120_IntClear_assertGPIOIntClear_LSB 0x1C
#define QIB_6120_IntClear_assertGPIOIntClear_RMASK 0x1
#define QIB_6120_IntClear_Reserved_LSB 0xF
#define QIB_6120_IntClear_Reserved_RMASK 0x1FFF
#define QIB_6120_IntClear_RcvAvail4IntClear_LSB 0x10
#define QIB_6120_IntClear_RcvAvail4IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvAvail3IntClear_LSB 0xF
#define QIB_6120_IntClear_RcvAvail3IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvAvail2IntClear_LSB 0xE
#define QIB_6120_IntClear_RcvAvail2IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvAvail1IntClear_LSB 0xD
#define QIB_6120_IntClear_RcvAvail1IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvAvail0IntClear_LSB 0xC
#define QIB_6120_IntClear_RcvAvail0IntClear_RMASK 0x1
#define QIB_6120_IntClear_Reserved1_LSB 0x5
#define QIB_6120_IntClear_Reserved1_RMASK 0x7F
#define QIB_6120_IntClear_RcvUrg4IntClear_LSB 0x4
#define QIB_6120_IntClear_RcvUrg4IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvUrg3IntClear_LSB 0x3
#define QIB_6120_IntClear_RcvUrg3IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvUrg2IntClear_LSB 0x2
#define QIB_6120_IntClear_RcvUrg2IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvUrg1IntClear_LSB 0x1
#define QIB_6120_IntClear_RcvUrg1IntClear_RMASK 0x1
#define QIB_6120_IntClear_RcvUrg0IntClear_LSB 0x0
#define QIB_6120_IntClear_RcvUrg0IntClear_RMASK 0x1

#define QIB_6120_ErrMask_OFFS 0x80
#define QIB_6120_ErrMask_Reserved_LSB 0x34
#define QIB_6120_ErrMask_Reserved_RMASK 0xFFF
#define QIB_6120_ErrMask_HardwareErrMask_LSB 0x33
#define QIB_6120_ErrMask_HardwareErrMask_RMASK 0x1
#define QIB_6120_ErrMask_ResetNegatedMask_LSB 0x32
#define QIB_6120_ErrMask_ResetNegatedMask_RMASK 0x1
#define QIB_6120_ErrMask_InvalidAddrErrMask_LSB 0x31
#define QIB_6120_ErrMask_InvalidAddrErrMask_RMASK 0x1
#define QIB_6120_ErrMask_IBStatusChangedMask_LSB 0x30
#define QIB_6120_ErrMask_IBStatusChangedMask_RMASK 0x1
#define QIB_6120_ErrMask_Reserved1_LSB 0x26
#define QIB_6120_ErrMask_Reserved1_RMASK 0x3FF
#define QIB_6120_ErrMask_SendUnsupportedVLErrMask_LSB 0x25
#define QIB_6120_ErrMask_SendUnsupportedVLErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendUnexpectedPktNumErrMask_LSB 0x24
#define QIB_6120_ErrMask_SendUnexpectedPktNumErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendPioArmLaunchErrMask_LSB 0x23
#define QIB_6120_ErrMask_SendPioArmLaunchErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendDroppedDataPktErrMask_LSB 0x22
#define QIB_6120_ErrMask_SendDroppedDataPktErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendDroppedSmpPktErrMask_LSB 0x21
#define QIB_6120_ErrMask_SendDroppedSmpPktErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendPktLenErrMask_LSB 0x20
#define QIB_6120_ErrMask_SendPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendUnderRunErrMask_LSB 0x1F
#define QIB_6120_ErrMask_SendUnderRunErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendMaxPktLenErrMask_LSB 0x1E
#define QIB_6120_ErrMask_SendMaxPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_SendMinPktLenErrMask_LSB 0x1D
#define QIB_6120_ErrMask_SendMinPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_Reserved2_LSB 0x12
#define QIB_6120_ErrMask_Reserved2_RMASK 0x7FF
#define QIB_6120_ErrMask_RcvIBLostLinkErrMask_LSB 0x11
#define QIB_6120_ErrMask_RcvIBLostLinkErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvHdrErrMask_LSB 0x10
#define QIB_6120_ErrMask_RcvHdrErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvHdrLenErrMask_LSB 0xF
#define QIB_6120_ErrMask_RcvHdrLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvBadTidErrMask_LSB 0xE
#define QIB_6120_ErrMask_RcvBadTidErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvHdrFullErrMask_LSB 0xD
#define QIB_6120_ErrMask_RcvHdrFullErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvEgrFullErrMask_LSB 0xC
#define QIB_6120_ErrMask_RcvEgrFullErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvBadVersionErrMask_LSB 0xB
#define QIB_6120_ErrMask_RcvBadVersionErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvIBFlowErrMask_LSB 0xA
#define QIB_6120_ErrMask_RcvIBFlowErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvEBPErrMask_LSB 0x9
#define QIB_6120_ErrMask_RcvEBPErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvUnsupportedVLErrMask_LSB 0x8
#define QIB_6120_ErrMask_RcvUnsupportedVLErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvUnexpectedCharErrMask_LSB 0x7
#define QIB_6120_ErrMask_RcvUnexpectedCharErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvShortPktLenErrMask_LSB 0x6
#define QIB_6120_ErrMask_RcvShortPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvLongPktLenErrMask_LSB 0x5
#define QIB_6120_ErrMask_RcvLongPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvMaxPktLenErrMask_LSB 0x4
#define QIB_6120_ErrMask_RcvMaxPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvMinPktLenErrMask_LSB 0x3
#define QIB_6120_ErrMask_RcvMinPktLenErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvICRCErrMask_LSB 0x2
#define QIB_6120_ErrMask_RcvICRCErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvVCRCErrMask_LSB 0x1
#define QIB_6120_ErrMask_RcvVCRCErrMask_RMASK 0x1
#define QIB_6120_ErrMask_RcvFormatErrMask_LSB 0x0
#define QIB_6120_ErrMask_RcvFormatErrMask_RMASK 0x1

#define QIB_6120_ErrStatus_OFFS 0x88
#define QIB_6120_ErrStatus_Reserved_LSB 0x34
#define QIB_6120_ErrStatus_Reserved_RMASK 0xFFF
#define QIB_6120_ErrStatus_HardwareErr_LSB 0x33
#define QIB_6120_ErrStatus_HardwareErr_RMASK 0x1
#define QIB_6120_ErrStatus_ResetNegated_LSB 0x32
#define QIB_6120_ErrStatus_ResetNegated_RMASK 0x1
#define QIB_6120_ErrStatus_InvalidAddrErr_LSB 0x31
#define QIB_6120_ErrStatus_InvalidAddrErr_RMASK 0x1
#define QIB_6120_ErrStatus_IBStatusChanged_LSB 0x30
#define QIB_6120_ErrStatus_IBStatusChanged_RMASK 0x1
#define QIB_6120_ErrStatus_Reserved1_LSB 0x26
#define QIB_6120_ErrStatus_Reserved1_RMASK 0x3FF
#define QIB_6120_ErrStatus_SendUnsupportedVLErr_LSB 0x25
#define QIB_6120_ErrStatus_SendUnsupportedVLErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendUnexpectedPktNumErr_LSB 0x24
#define QIB_6120_ErrStatus_SendUnexpectedPktNumErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendPioArmLaunchErr_LSB 0x23
#define QIB_6120_ErrStatus_SendPioArmLaunchErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendDroppedDataPktErr_LSB 0x22
#define QIB_6120_ErrStatus_SendDroppedDataPktErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendDroppedSmpPktErr_LSB 0x21
#define QIB_6120_ErrStatus_SendDroppedSmpPktErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendPktLenErr_LSB 0x20
#define QIB_6120_ErrStatus_SendPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendUnderRunErr_LSB 0x1F
#define QIB_6120_ErrStatus_SendUnderRunErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendMaxPktLenErr_LSB 0x1E
#define QIB_6120_ErrStatus_SendMaxPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_SendMinPktLenErr_LSB 0x1D
#define QIB_6120_ErrStatus_SendMinPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_Reserved2_LSB 0x12
#define QIB_6120_ErrStatus_Reserved2_RMASK 0x7FF
#define QIB_6120_ErrStatus_RcvIBLostLinkErr_LSB 0x11
#define QIB_6120_ErrStatus_RcvIBLostLinkErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvHdrErr_LSB 0x10
#define QIB_6120_ErrStatus_RcvHdrErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvHdrLenErr_LSB 0xF
#define QIB_6120_ErrStatus_RcvHdrLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvBadTidErr_LSB 0xE
#define QIB_6120_ErrStatus_RcvBadTidErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvHdrFullErr_LSB 0xD
#define QIB_6120_ErrStatus_RcvHdrFullErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvEgrFullErr_LSB 0xC
#define QIB_6120_ErrStatus_RcvEgrFullErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvBadVersionErr_LSB 0xB
#define QIB_6120_ErrStatus_RcvBadVersionErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvIBFlowErr_LSB 0xA
#define QIB_6120_ErrStatus_RcvIBFlowErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvEBPErr_LSB 0x9
#define QIB_6120_ErrStatus_RcvEBPErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvUnsupportedVLErr_LSB 0x8
#define QIB_6120_ErrStatus_RcvUnsupportedVLErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvUnexpectedCharErr_LSB 0x7
#define QIB_6120_ErrStatus_RcvUnexpectedCharErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvShortPktLenErr_LSB 0x6
#define QIB_6120_ErrStatus_RcvShortPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvLongPktLenErr_LSB 0x5
#define QIB_6120_ErrStatus_RcvLongPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvMaxPktLenErr_LSB 0x4
#define QIB_6120_ErrStatus_RcvMaxPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvMinPktLenErr_LSB 0x3
#define QIB_6120_ErrStatus_RcvMinPktLenErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvICRCErr_LSB 0x2
#define QIB_6120_ErrStatus_RcvICRCErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvVCRCErr_LSB 0x1
#define QIB_6120_ErrStatus_RcvVCRCErr_RMASK 0x1
#define QIB_6120_ErrStatus_RcvFormatErr_LSB 0x0
#define QIB_6120_ErrStatus_RcvFormatErr_RMASK 0x1

#define QIB_6120_ErrClear_OFFS 0x90
#define QIB_6120_ErrClear_Reserved_LSB 0x34
#define QIB_6120_ErrClear_Reserved_RMASK 0xFFF
#define QIB_6120_ErrClear_HardwareErrClear_LSB 0x33
#define QIB_6120_ErrClear_HardwareErrClear_RMASK 0x1
#define QIB_6120_ErrClear_ResetNegatedClear_LSB 0x32
#define QIB_6120_ErrClear_ResetNegatedClear_RMASK 0x1
#define QIB_6120_ErrClear_InvalidAddrErrClear_LSB 0x31
#define QIB_6120_ErrClear_InvalidAddrErrClear_RMASK 0x1
#define QIB_6120_ErrClear_IBStatusChangedClear_LSB 0x30
#define QIB_6120_ErrClear_IBStatusChangedClear_RMASK 0x1
#define QIB_6120_ErrClear_Reserved1_LSB 0x26
#define QIB_6120_ErrClear_Reserved1_RMASK 0x3FF
#define QIB_6120_ErrClear_SendUnsupportedVLErrClear_LSB 0x25
#define QIB_6120_ErrClear_SendUnsupportedVLErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendUnexpectedPktNumErrClear_LSB 0x24
#define QIB_6120_ErrClear_SendUnexpectedPktNumErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendPioArmLaunchErrClear_LSB 0x23
#define QIB_6120_ErrClear_SendPioArmLaunchErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendDroppedDataPktErrClear_LSB 0x22
#define QIB_6120_ErrClear_SendDroppedDataPktErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendDroppedSmpPktErrClear_LSB 0x21
#define QIB_6120_ErrClear_SendDroppedSmpPktErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendPktLenErrClear_LSB 0x20
#define QIB_6120_ErrClear_SendPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendUnderRunErrClear_LSB 0x1F
#define QIB_6120_ErrClear_SendUnderRunErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendMaxPktLenErrClear_LSB 0x1E
#define QIB_6120_ErrClear_SendMaxPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_SendMinPktLenErrClear_LSB 0x1D
#define QIB_6120_ErrClear_SendMinPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_Reserved2_LSB 0x12
#define QIB_6120_ErrClear_Reserved2_RMASK 0x7FF
#define QIB_6120_ErrClear_RcvIBLostLinkErrClear_LSB 0x11
#define QIB_6120_ErrClear_RcvIBLostLinkErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvHdrErrClear_LSB 0x10
#define QIB_6120_ErrClear_RcvHdrErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvHdrLenErrClear_LSB 0xF
#define QIB_6120_ErrClear_RcvHdrLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvBadTidErrClear_LSB 0xE
#define QIB_6120_ErrClear_RcvBadTidErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvHdrFullErrClear_LSB 0xD
#define QIB_6120_ErrClear_RcvHdrFullErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvEgrFullErrClear_LSB 0xC
#define QIB_6120_ErrClear_RcvEgrFullErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvBadVersionErrClear_LSB 0xB
#define QIB_6120_ErrClear_RcvBadVersionErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvIBFlowErrClear_LSB 0xA
#define QIB_6120_ErrClear_RcvIBFlowErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvEBPErrClear_LSB 0x9
#define QIB_6120_ErrClear_RcvEBPErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvUnsupportedVLErrClear_LSB 0x8
#define QIB_6120_ErrClear_RcvUnsupportedVLErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvUnexpectedCharErrClear_LSB 0x7
#define QIB_6120_ErrClear_RcvUnexpectedCharErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvShortPktLenErrClear_LSB 0x6
#define QIB_6120_ErrClear_RcvShortPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvLongPktLenErrClear_LSB 0x5
#define QIB_6120_ErrClear_RcvLongPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvMaxPktLenErrClear_LSB 0x4
#define QIB_6120_ErrClear_RcvMaxPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvMinPktLenErrClear_LSB 0x3
#define QIB_6120_ErrClear_RcvMinPktLenErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvICRCErrClear_LSB 0x2
#define QIB_6120_ErrClear_RcvICRCErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvVCRCErrClear_LSB 0x1
#define QIB_6120_ErrClear_RcvVCRCErrClear_RMASK 0x1
#define QIB_6120_ErrClear_RcvFormatErrClear_LSB 0x0
#define QIB_6120_ErrClear_RcvFormatErrClear_RMASK 0x1

#define QIB_6120_HwErrMask_OFFS 0x98
#define QIB_6120_HwErrMask_IBCBusFromSPCParityErrMask_LSB 0x3F
#define QIB_6120_HwErrMask_IBCBusFromSPCParityErrMask_RMASK 0x1
#define QIB_6120_HwErrMask_IBCBusToSPCParityErrMask_LSB 0x3E
#define QIB_6120_HwErrMask_IBCBusToSPCParityErrMask_RMASK 0x1
#define QIB_6120_HwErrMask_Reserved_LSB 0x3D
#define QIB_6120_HwErrMask_Reserved_RMASK 0x1
#define QIB_6120_HwErrMask_IBSerdesPClkNotDetectMask_LSB 0x3C
#define QIB_6120_HwErrMask_IBSerdesPClkNotDetectMask_RMASK 0x1
#define QIB_6120_HwErrMask_PCIESerdesQ0PClkNotDetectMask_LSB 0x3B
#define QIB_6120_HwErrMask_PCIESerdesQ0PClkNotDetectMask_RMASK 0x1
#define QIB_6120_HwErrMask_PCIESerdesQ1PClkNotDetectMask_LSB 0x3A
#define QIB_6120_HwErrMask_PCIESerdesQ1PClkNotDetectMask_RMASK 0x1
#define QIB_6120_HwErrMask_Reserved1_LSB 0x39
#define QIB_6120_HwErrMask_Reserved1_RMASK 0x1
#define QIB_6120_HwErrMask_IBPLLrfSlipMask_LSB 0x38
#define QIB_6120_HwErrMask_IBPLLrfSlipMask_RMASK 0x1
#define QIB_6120_HwErrMask_IBPLLfbSlipMask_LSB 0x37
#define QIB_6120_HwErrMask_IBPLLfbSlipMask_RMASK 0x1
#define QIB_6120_HwErrMask_PowerOnBISTFailedMask_LSB 0x36
#define QIB_6120_HwErrMask_PowerOnBISTFailedMask_RMASK 0x1
#define QIB_6120_HwErrMask_Reserved2_LSB 0x33
#define QIB_6120_HwErrMask_Reserved2_RMASK 0x7
#define QIB_6120_HwErrMask_RXEMemParityErrMask_LSB 0x2C
#define QIB_6120_HwErrMask_RXEMemParityErrMask_RMASK 0x7F
#define QIB_6120_HwErrMask_TXEMemParityErrMask_LSB 0x28
#define QIB_6120_HwErrMask_TXEMemParityErrMask_RMASK 0xF
#define QIB_6120_HwErrMask_Reserved3_LSB 0x22
#define QIB_6120_HwErrMask_Reserved3_RMASK 0x3F
#define QIB_6120_HwErrMask_PCIeBusParityErrMask_LSB 0x1F
#define QIB_6120_HwErrMask_PCIeBusParityErrMask_RMASK 0x7
#define QIB_6120_HwErrMask_PcieCplTimeoutMask_LSB 0x1E
#define QIB_6120_HwErrMask_PcieCplTimeoutMask_RMASK 0x1
#define QIB_6120_HwErrMask_PoisonedTLPMask_LSB 0x1D
#define QIB_6120_HwErrMask_PoisonedTLPMask_RMASK 0x1
#define QIB_6120_HwErrMask_Reserved4_LSB 0x6
#define QIB_6120_HwErrMask_Reserved4_RMASK 0x7FFFFF
#define QIB_6120_HwErrMask_PCIeMemParityErrMask_LSB 0x0
#define QIB_6120_HwErrMask_PCIeMemParityErrMask_RMASK 0x3F

#define QIB_6120_HwErrStatus_OFFS 0xA0
#define QIB_6120_HwErrStatus_IBCBusFromSPCParityErr_LSB 0x3F
#define QIB_6120_HwErrStatus_IBCBusFromSPCParityErr_RMASK 0x1
#define QIB_6120_HwErrStatus_IBCBusToSPCParityErr_LSB 0x3E
#define QIB_6120_HwErrStatus_IBCBusToSPCParityErr_RMASK 0x1
#define QIB_6120_HwErrStatus_Reserved_LSB 0x3D
#define QIB_6120_HwErrStatus_Reserved_RMASK 0x1
#define QIB_6120_HwErrStatus_IBSerdesPClkNotDetect_LSB 0x3C
#define QIB_6120_HwErrStatus_IBSerdesPClkNotDetect_RMASK 0x1
#define QIB_6120_HwErrStatus_PCIESerdesQ0PClkNotDetect_LSB 0x3B
#define QIB_6120_HwErrStatus_PCIESerdesQ0PClkNotDetect_RMASK 0x1
#define QIB_6120_HwErrStatus_PCIESerdesQ1PClkNotDetect_LSB 0x3A
#define QIB_6120_HwErrStatus_PCIESerdesQ1PClkNotDetect_RMASK 0x1
#define QIB_6120_HwErrStatus_Reserved1_LSB 0x39
#define QIB_6120_HwErrStatus_Reserved1_RMASK 0x1
#define QIB_6120_HwErrStatus_IBPLLrfSlip_LSB 0x38
#define QIB_6120_HwErrStatus_IBPLLrfSlip_RMASK 0x1
#define QIB_6120_HwErrStatus_IBPLLfbSlip_LSB 0x37
#define QIB_6120_HwErrStatus_IBPLLfbSlip_RMASK 0x1
#define QIB_6120_HwErrStatus_PowerOnBISTFailed_LSB 0x36
#define QIB_6120_HwErrStatus_PowerOnBISTFailed_RMASK 0x1
#define QIB_6120_HwErrStatus_Reserved2_LSB 0x33
#define QIB_6120_HwErrStatus_Reserved2_RMASK 0x7
#define QIB_6120_HwErrStatus_RXEMemParity_LSB 0x2C
#define QIB_6120_HwErrStatus_RXEMemParity_RMASK 0x7F
#define QIB_6120_HwErrStatus_TXEMemParity_LSB 0x28
#define QIB_6120_HwErrStatus_TXEMemParity_RMASK 0xF
#define QIB_6120_HwErrStatus_Reserved3_LSB 0x22
#define QIB_6120_HwErrStatus_Reserved3_RMASK 0x3F
#define QIB_6120_HwErrStatus_PCIeBusParity_LSB 0x1F
#define QIB_6120_HwErrStatus_PCIeBusParity_RMASK 0x7
#define QIB_6120_HwErrStatus_PcieCplTimeout_LSB 0x1E
#define QIB_6120_HwErrStatus_PcieCplTimeout_RMASK 0x1
#define QIB_6120_HwErrStatus_PoisenedTLP_LSB 0x1D
#define QIB_6120_HwErrStatus_PoisenedTLP_RMASK 0x1
#define QIB_6120_HwErrStatus_Reserved4_LSB 0x6
#define QIB_6120_HwErrStatus_Reserved4_RMASK 0x7FFFFF
#define QIB_6120_HwErrStatus_PCIeMemParity_LSB 0x0
#define QIB_6120_HwErrStatus_PCIeMemParity_RMASK 0x3F

#define QIB_6120_HwErrClear_OFFS 0xA8
#define QIB_6120_HwErrClear_IBCBusFromSPCParityErrClear_LSB 0x3F
#define QIB_6120_HwErrClear_IBCBusFromSPCParityErrClear_RMASK 0x1
#define QIB_6120_HwErrClear_IBCBusToSPCparityErrClear_LSB 0x3E
#define QIB_6120_HwErrClear_IBCBusToSPCparityErrClear_RMASK 0x1
#define QIB_6120_HwErrClear_Reserved_LSB 0x3D
#define QIB_6120_HwErrClear_Reserved_RMASK 0x1
#define QIB_6120_HwErrClear_IBSerdesPClkNotDetectClear_LSB 0x3C
#define QIB_6120_HwErrClear_IBSerdesPClkNotDetectClear_RMASK 0x1
#define QIB_6120_HwErrClear_PCIESerdesQ0PClkNotDetectClear_LSB 0x3B
#define QIB_6120_HwErrClear_PCIESerdesQ0PClkNotDetectClear_RMASK 0x1
#define QIB_6120_HwErrClear_PCIESerdesQ1PClkNotDetectClear_LSB 0x3A
#define QIB_6120_HwErrClear_PCIESerdesQ1PClkNotDetectClear_RMASK 0x1
#define QIB_6120_HwErrClear_Reserved1_LSB 0x39
#define QIB_6120_HwErrClear_Reserved1_RMASK 0x1
#define QIB_6120_HwErrClear_IBPLLrfSlipClear_LSB 0x38
#define QIB_6120_HwErrClear_IBPLLrfSlipClear_RMASK 0x1
#define QIB_6120_HwErrClear_IBPLLfbSlipClear_LSB 0x37
#define QIB_6120_HwErrClear_IBPLLfbSlipClear_RMASK 0x1
#define QIB_6120_HwErrClear_PowerOnBISTFailedClear_LSB 0x36
#define QIB_6120_HwErrClear_PowerOnBISTFailedClear_RMASK 0x1
#define QIB_6120_HwErrClear_Reserved2_LSB 0x33
#define QIB_6120_HwErrClear_Reserved2_RMASK 0x7
#define QIB_6120_HwErrClear_RXEMemParityClear_LSB 0x2C
#define QIB_6120_HwErrClear_RXEMemParityClear_RMASK 0x7F
#define QIB_6120_HwErrClear_TXEMemParityClear_LSB 0x28
#define QIB_6120_HwErrClear_TXEMemParityClear_RMASK 0xF
#define QIB_6120_HwErrClear_Reserved3_LSB 0x22
#define QIB_6120_HwErrClear_Reserved3_RMASK 0x3F
#define QIB_6120_HwErrClear_PCIeBusParityClr_LSB 0x1F
#define QIB_6120_HwErrClear_PCIeBusParityClr_RMASK 0x7
#define QIB_6120_HwErrClear_PcieCplTimeoutClear_LSB 0x1E
#define QIB_6120_HwErrClear_PcieCplTimeoutClear_RMASK 0x1
#define QIB_6120_HwErrClear_PoisonedTLPClear_LSB 0x1D
#define QIB_6120_HwErrClear_PoisonedTLPClear_RMASK 0x1
#define QIB_6120_HwErrClear_Reserved4_LSB 0x6
#define QIB_6120_HwErrClear_Reserved4_RMASK 0x7FFFFF
#define QIB_6120_HwErrClear_PCIeMemParityClr_LSB 0x0
#define QIB_6120_HwErrClear_PCIeMemParityClr_RMASK 0x3F

#define QIB_6120_HwDiagCtrl_OFFS 0xB0
#define QIB_6120_HwDiagCtrl_ForceIBCBusFromSPCParityErr_LSB 0x3F
#define QIB_6120_HwDiagCtrl_ForceIBCBusFromSPCParityErr_RMASK 0x1
#define QIB_6120_HwDiagCtrl_ForceIBCBusToSPCParityErr_LSB 0x3E
#define QIB_6120_HwDiagCtrl_ForceIBCBusToSPCParityErr_RMASK 0x1
#define QIB_6120_HwDiagCtrl_CounterWrEnable_LSB 0x3D
#define QIB_6120_HwDiagCtrl_CounterWrEnable_RMASK 0x1
#define QIB_6120_HwDiagCtrl_CounterDisable_LSB 0x3C
#define QIB_6120_HwDiagCtrl_CounterDisable_RMASK 0x1
#define QIB_6120_HwDiagCtrl_Reserved_LSB 0x33
#define QIB_6120_HwDiagCtrl_Reserved_RMASK 0x1FF
#define QIB_6120_HwDiagCtrl_ForceRxMemParityErr_LSB 0x2C
#define QIB_6120_HwDiagCtrl_ForceRxMemParityErr_RMASK 0x7F
#define QIB_6120_HwDiagCtrl_ForceTxMemparityErr_LSB 0x28
#define QIB_6120_HwDiagCtrl_ForceTxMemparityErr_RMASK 0xF
#define QIB_6120_HwDiagCtrl_Reserved1_LSB 0x23
#define QIB_6120_HwDiagCtrl_Reserved1_RMASK 0x1F
#define QIB_6120_HwDiagCtrl_forcePCIeBusParity_LSB 0x1F
#define QIB_6120_HwDiagCtrl_forcePCIeBusParity_RMASK 0xF
#define QIB_6120_HwDiagCtrl_Reserved2_LSB 0x6
#define QIB_6120_HwDiagCtrl_Reserved2_RMASK 0x1FFFFFF
#define QIB_6120_HwDiagCtrl_forcePCIeMemParity_LSB 0x0
#define QIB_6120_HwDiagCtrl_forcePCIeMemParity_RMASK 0x3F

#define QIB_6120_IBCStatus_OFFS 0xC0
#define QIB_6120_IBCStatus_TxCreditOk_LSB 0x1F
#define QIB_6120_IBCStatus_TxCreditOk_RMASK 0x1
#define QIB_6120_IBCStatus_TxReady_LSB 0x1E
#define QIB_6120_IBCStatus_TxReady_RMASK 0x1
#define QIB_6120_IBCStatus_Reserved_LSB 0x7
#define QIB_6120_IBCStatus_Reserved_RMASK 0x7FFFFF
#define QIB_6120_IBCStatus_LinkState_LSB 0x4
#define QIB_6120_IBCStatus_LinkState_RMASK 0x7
#define QIB_6120_IBCStatus_LinkTrainingState_LSB 0x0
#define QIB_6120_IBCStatus_LinkTrainingState_RMASK 0xF

#define QIB_6120_IBCCtrl_OFFS 0xC8
#define QIB_6120_IBCCtrl_Loopback_LSB 0x3F
#define QIB_6120_IBCCtrl_Loopback_RMASK 0x1
#define QIB_6120_IBCCtrl_LinkDownDefaultState_LSB 0x3E
#define QIB_6120_IBCCtrl_LinkDownDefaultState_RMASK 0x1
#define QIB_6120_IBCCtrl_Reserved_LSB 0x2B
#define QIB_6120_IBCCtrl_Reserved_RMASK 0x7FFFF
#define QIB_6120_IBCCtrl_CreditScale_LSB 0x28
#define QIB_6120_IBCCtrl_CreditScale_RMASK 0x7
#define QIB_6120_IBCCtrl_OverrunThreshold_LSB 0x24
#define QIB_6120_IBCCtrl_OverrunThreshold_RMASK 0xF
#define QIB_6120_IBCCtrl_PhyerrThreshold_LSB 0x20
#define QIB_6120_IBCCtrl_PhyerrThreshold_RMASK 0xF
#define QIB_6120_IBCCtrl_Reserved1_LSB 0x1F
#define QIB_6120_IBCCtrl_Reserved1_RMASK 0x1
#define QIB_6120_IBCCtrl_MaxPktLen_LSB 0x14
#define QIB_6120_IBCCtrl_MaxPktLen_RMASK 0x7FF
#define QIB_6120_IBCCtrl_LinkCmd_LSB 0x12
#define QIB_6120_IBCCtrl_LinkCmd_RMASK 0x3
#define QIB_6120_IBCCtrl_LinkInitCmd_LSB 0x10
#define QIB_6120_IBCCtrl_LinkInitCmd_RMASK 0x3
#define QIB_6120_IBCCtrl_FlowCtrlWaterMark_LSB 0x8
#define QIB_6120_IBCCtrl_FlowCtrlWaterMark_RMASK 0xFF
#define QIB_6120_IBCCtrl_FlowCtrlPeriod_LSB 0x0
#define QIB_6120_IBCCtrl_FlowCtrlPeriod_RMASK 0xFF

#define QIB_6120_EXTStatus_OFFS 0xD0
#define QIB_6120_EXTStatus_GPIOIn_LSB 0x30
#define QIB_6120_EXTStatus_GPIOIn_RMASK 0xFFFF
#define QIB_6120_EXTStatus_Reserved_LSB 0x20
#define QIB_6120_EXTStatus_Reserved_RMASK 0xFFFF
#define QIB_6120_EXTStatus_Reserved1_LSB 0x10
#define QIB_6120_EXTStatus_Reserved1_RMASK 0xFFFF
#define QIB_6120_EXTStatus_MemBISTFoundErr_LSB 0xF
#define QIB_6120_EXTStatus_MemBISTFoundErr_RMASK 0x1
#define QIB_6120_EXTStatus_MemBISTEndTest_LSB 0xE
#define QIB_6120_EXTStatus_MemBISTEndTest_RMASK 0x1
#define QIB_6120_EXTStatus_Reserved2_LSB 0x0
#define QIB_6120_EXTStatus_Reserved2_RMASK 0x3FFF

#define QIB_6120_EXTCtrl_OFFS 0xD8
#define QIB_6120_EXTCtrl_GPIOOe_LSB 0x30
#define QIB_6120_EXTCtrl_GPIOOe_RMASK 0xFFFF
#define QIB_6120_EXTCtrl_GPIOInvert_LSB 0x20
#define QIB_6120_EXTCtrl_GPIOInvert_RMASK 0xFFFF
#define QIB_6120_EXTCtrl_Reserved_LSB 0x4
#define QIB_6120_EXTCtrl_Reserved_RMASK 0xFFFFFFF
#define QIB_6120_EXTCtrl_LEDPriPortGreenOn_LSB 0x3
#define QIB_6120_EXTCtrl_LEDPriPortGreenOn_RMASK 0x1
#define QIB_6120_EXTCtrl_LEDPriPortYellowOn_LSB 0x2
#define QIB_6120_EXTCtrl_LEDPriPortYellowOn_RMASK 0x1
#define QIB_6120_EXTCtrl_LEDGblOkGreenOn_LSB 0x1
#define QIB_6120_EXTCtrl_LEDGblOkGreenOn_RMASK 0x1
#define QIB_6120_EXTCtrl_LEDGblErrRedOff_LSB 0x0
#define QIB_6120_EXTCtrl_LEDGblErrRedOff_RMASK 0x1

#define QIB_6120_GPIOOut_OFFS 0xE0

#define QIB_6120_GPIOMask_OFFS 0xE8

#define QIB_6120_GPIOStatus_OFFS 0xF0

#define QIB_6120_GPIOClear_OFFS 0xF8

#define QIB_6120_RcvCtrl_OFFS 0x100
#define QIB_6120_RcvCtrl_TailUpd_LSB 0x1F
#define QIB_6120_RcvCtrl_TailUpd_RMASK 0x1
#define QIB_6120_RcvCtrl_RcvPartitionKeyDisable_LSB 0x1E
#define QIB_6120_RcvCtrl_RcvPartitionKeyDisable_RMASK 0x1
#define QIB_6120_RcvCtrl_Reserved_LSB 0x15
#define QIB_6120_RcvCtrl_Reserved_RMASK 0x1FF
#define QIB_6120_RcvCtrl_IntrAvail_LSB 0x10
#define QIB_6120_RcvCtrl_IntrAvail_RMASK 0x1F
#define QIB_6120_RcvCtrl_Reserved1_LSB 0x9
#define QIB_6120_RcvCtrl_Reserved1_RMASK 0x7F
#define QIB_6120_RcvCtrl_Reserved2_LSB 0x5
#define QIB_6120_RcvCtrl_Reserved2_RMASK 0xF
#define QIB_6120_RcvCtrl_PortEnable_LSB 0x0
#define QIB_6120_RcvCtrl_PortEnable_RMASK 0x1F

#define QIB_6120_RcvBTHQP_OFFS 0x108
#define QIB_6120_RcvBTHQP_BTHQP_Mask_LSB 0x1E
#define QIB_6120_RcvBTHQP_BTHQP_Mask_RMASK 0x3
#define QIB_6120_RcvBTHQP_Reserved_LSB 0x18
#define QIB_6120_RcvBTHQP_Reserved_RMASK 0x3F
#define QIB_6120_RcvBTHQP_RcvBTHQP_LSB 0x0
#define QIB_6120_RcvBTHQP_RcvBTHQP_RMASK 0xFFFFFF

#define QIB_6120_RcvHdrSize_OFFS 0x110

#define QIB_6120_RcvHdrCnt_OFFS 0x118

#define QIB_6120_RcvHdrEntSize_OFFS 0x120

#define QIB_6120_RcvTIDBase_OFFS 0x128

#define QIB_6120_RcvTIDCnt_OFFS 0x130

#define QIB_6120_RcvEgrBase_OFFS 0x138

#define QIB_6120_RcvEgrCnt_OFFS 0x140

#define QIB_6120_RcvBufBase_OFFS 0x148

#define QIB_6120_RcvBufSize_OFFS 0x150

#define QIB_6120_RxIntMemBase_OFFS 0x158

#define QIB_6120_RxIntMemSize_OFFS 0x160

#define QIB_6120_RcvPartitionKey_OFFS 0x168

#define QIB_6120_RcvPktLEDCnt_OFFS 0x178
#define QIB_6120_RcvPktLEDCnt_ONperiod_LSB 0x20
#define QIB_6120_RcvPktLEDCnt_ONperiod_RMASK 0xFFFFFFFF
#define QIB_6120_RcvPktLEDCnt_OFFperiod_LSB 0x0
#define QIB_6120_RcvPktLEDCnt_OFFperiod_RMASK 0xFFFFFFFF

#define QIB_6120_SendCtrl_OFFS 0x1C0
#define QIB_6120_SendCtrl_Disarm_LSB 0x1F
#define QIB_6120_SendCtrl_Disarm_RMASK 0x1
#define QIB_6120_SendCtrl_Reserved_LSB 0x17
#define QIB_6120_SendCtrl_Reserved_RMASK 0xFF
#define QIB_6120_SendCtrl_DisarmPIOBuf_LSB 0x10
#define QIB_6120_SendCtrl_DisarmPIOBuf_RMASK 0x7F
#define QIB_6120_SendCtrl_Reserved1_LSB 0x4
#define QIB_6120_SendCtrl_Reserved1_RMASK 0xFFF
#define QIB_6120_SendCtrl_PIOEnable_LSB 0x3
#define QIB_6120_SendCtrl_PIOEnable_RMASK 0x1
#define QIB_6120_SendCtrl_PIOBufAvailUpd_LSB 0x2
#define QIB_6120_SendCtrl_PIOBufAvailUpd_RMASK 0x1
#define QIB_6120_SendCtrl_PIOIntBufAvail_LSB 0x1
#define QIB_6120_SendCtrl_PIOIntBufAvail_RMASK 0x1
#define QIB_6120_SendCtrl_Abort_LSB 0x0
#define QIB_6120_SendCtrl_Abort_RMASK 0x1

#define QIB_6120_SendPIOBufBase_OFFS 0x1C8
#define QIB_6120_SendPIOBufBase_Reserved_LSB 0x35
#define QIB_6120_SendPIOBufBase_Reserved_RMASK 0x7FF
#define QIB_6120_SendPIOBufBase_BaseAddr_LargePIO_LSB 0x20
#define QIB_6120_SendPIOBufBase_BaseAddr_LargePIO_RMASK 0x1FFFFF
#define QIB_6120_SendPIOBufBase_Reserved1_LSB 0x15
#define QIB_6120_SendPIOBufBase_Reserved1_RMASK 0x7FF
#define QIB_6120_SendPIOBufBase_BaseAddr_SmallPIO_LSB 0x0
#define QIB_6120_SendPIOBufBase_BaseAddr_SmallPIO_RMASK 0x1FFFFF

#define QIB_6120_SendPIOSize_OFFS 0x1D0
#define QIB_6120_SendPIOSize_Reserved_LSB 0x2D
#define QIB_6120_SendPIOSize_Reserved_RMASK 0xFFFFF
#define QIB_6120_SendPIOSize_Size_LargePIO_LSB 0x20
#define QIB_6120_SendPIOSize_Size_LargePIO_RMASK 0x1FFF
#define QIB_6120_SendPIOSize_Reserved1_LSB 0xC
#define QIB_6120_SendPIOSize_Reserved1_RMASK 0xFFFFF
#define QIB_6120_SendPIOSize_Size_SmallPIO_LSB 0x0
#define QIB_6120_SendPIOSize_Size_SmallPIO_RMASK 0xFFF

#define QIB_6120_SendPIOBufCnt_OFFS 0x1D8
#define QIB_6120_SendPIOBufCnt_Reserved_LSB 0x24
#define QIB_6120_SendPIOBufCnt_Reserved_RMASK 0xFFFFFFF
#define QIB_6120_SendPIOBufCnt_Num_LargePIO_LSB 0x20
#define QIB_6120_SendPIOBufCnt_Num_LargePIO_RMASK 0xF
#define QIB_6120_SendPIOBufCnt_Reserved1_LSB 0x9
#define QIB_6120_SendPIOBufCnt_Reserved1_RMASK 0x7FFFFF
#define QIB_6120_SendPIOBufCnt_Num_SmallPIO_LSB 0x0
#define QIB_6120_SendPIOBufCnt_Num_SmallPIO_RMASK 0x1FF

#define QIB_6120_SendPIOAvailAddr_OFFS 0x1E0
#define QIB_6120_SendPIOAvailAddr_SendPIOAvailAddr_LSB 0x6
#define QIB_6120_SendPIOAvailAddr_SendPIOAvailAddr_RMASK 0x3FFFFFFFF
#define QIB_6120_SendPIOAvailAddr_Reserved_LSB 0x0
#define QIB_6120_SendPIOAvailAddr_Reserved_RMASK 0x3F

#define QIB_6120_SendBufErr0_OFFS 0x240
#define QIB_6120_SendBufErr0_SendBufErrPIO_63_0_LSB 0x0
#define QIB_6120_SendBufErr0_SendBufErrPIO_63_0_RMASK 0x0

#define QIB_6120_RcvHdrAddr0_OFFS 0x280
#define QIB_6120_RcvHdrAddr0_RcvHdrAddr0_LSB 0x2
#define QIB_6120_RcvHdrAddr0_RcvHdrAddr0_RMASK 0x3FFFFFFFFF
#define QIB_6120_RcvHdrAddr0_Reserved_LSB 0x0
#define QIB_6120_RcvHdrAddr0_Reserved_RMASK 0x3

#define QIB_6120_RcvHdrTailAddr0_OFFS 0x300
#define QIB_6120_RcvHdrTailAddr0_RcvHdrTailAddr0_LSB 0x2
#define QIB_6120_RcvHdrTailAddr0_RcvHdrTailAddr0_RMASK 0x3FFFFFFFFF
#define QIB_6120_RcvHdrTailAddr0_Reserved_LSB 0x0
#define QIB_6120_RcvHdrTailAddr0_Reserved_RMASK 0x3

#define QIB_6120_SerdesCfg0_OFFS 0x3C0
#define QIB_6120_SerdesCfg0_DisableIBTxIdleDetect_LSB 0x3F
#define QIB_6120_SerdesCfg0_DisableIBTxIdleDetect_RMASK 0x1
#define QIB_6120_SerdesCfg0_Reserved_LSB 0x38
#define QIB_6120_SerdesCfg0_Reserved_RMASK 0x7F
#define QIB_6120_SerdesCfg0_RxEqCtl_LSB 0x36
#define QIB_6120_SerdesCfg0_RxEqCtl_RMASK 0x3
#define QIB_6120_SerdesCfg0_TxTermAdj_LSB 0x34
#define QIB_6120_SerdesCfg0_TxTermAdj_RMASK 0x3
#define QIB_6120_SerdesCfg0_RxTermAdj_LSB 0x32
#define QIB_6120_SerdesCfg0_RxTermAdj_RMASK 0x3
#define QIB_6120_SerdesCfg0_TermAdj1_LSB 0x31
#define QIB_6120_SerdesCfg0_TermAdj1_RMASK 0x1
#define QIB_6120_SerdesCfg0_TermAdj0_LSB 0x30
#define QIB_6120_SerdesCfg0_TermAdj0_RMASK 0x1
#define QIB_6120_SerdesCfg0_LPBKA_LSB 0x2F
#define QIB_6120_SerdesCfg0_LPBKA_RMASK 0x1
#define QIB_6120_SerdesCfg0_LPBKB_LSB 0x2E
#define QIB_6120_SerdesCfg0_LPBKB_RMASK 0x1
#define QIB_6120_SerdesCfg0_LPBKC_LSB 0x2D
#define QIB_6120_SerdesCfg0_LPBKC_RMASK 0x1
#define QIB_6120_SerdesCfg0_LPBKD_LSB 0x2C
#define QIB_6120_SerdesCfg0_LPBKD_RMASK 0x1
#define QIB_6120_SerdesCfg0_PW_LSB 0x2B
#define QIB_6120_SerdesCfg0_PW_RMASK 0x1
#define QIB_6120_SerdesCfg0_RefSel_LSB 0x29
#define QIB_6120_SerdesCfg0_RefSel_RMASK 0x3
#define QIB_6120_SerdesCfg0_ParReset_LSB 0x28
#define QIB_6120_SerdesCfg0_ParReset_RMASK 0x1
#define QIB_6120_SerdesCfg0_ParLPBK_LSB 0x27
#define QIB_6120_SerdesCfg0_ParLPBK_RMASK 0x1
#define QIB_6120_SerdesCfg0_OffsetEn_LSB 0x26
#define QIB_6120_SerdesCfg0_OffsetEn_RMASK 0x1
#define QIB_6120_SerdesCfg0_Offset_LSB 0x1E
#define QIB_6120_SerdesCfg0_Offset_RMASK 0xFF
#define QIB_6120_SerdesCfg0_L2PwrDn_LSB 0x1D
#define QIB_6120_SerdesCfg0_L2PwrDn_RMASK 0x1
#define QIB_6120_SerdesCfg0_ResetPLL_LSB 0x1C
#define QIB_6120_SerdesCfg0_ResetPLL_RMASK 0x1
#define QIB_6120_SerdesCfg0_RxTermEnX_LSB 0x18
#define QIB_6120_SerdesCfg0_RxTermEnX_RMASK 0xF
#define QIB_6120_SerdesCfg0_BeaconTxEnX_LSB 0x14
#define QIB_6120_SerdesCfg0_BeaconTxEnX_RMASK 0xF
#define QIB_6120_SerdesCfg0_RxDetEnX_LSB 0x10
#define QIB_6120_SerdesCfg0_RxDetEnX_RMASK 0xF
#define QIB_6120_SerdesCfg0_TxIdeEnX_LSB 0xC
#define QIB_6120_SerdesCfg0_TxIdeEnX_RMASK 0xF
#define QIB_6120_SerdesCfg0_RxIdleEnX_LSB 0x8
#define QIB_6120_SerdesCfg0_RxIdleEnX_RMASK 0xF
#define QIB_6120_SerdesCfg0_L1PwrDnA_LSB 0x7
#define QIB_6120_SerdesCfg0_L1PwrDnA_RMASK 0x1
#define QIB_6120_SerdesCfg0_L1PwrDnB_LSB 0x6
#define QIB_6120_SerdesCfg0_L1PwrDnB_RMASK 0x1
#define QIB_6120_SerdesCfg0_L1PwrDnC_LSB 0x5
#define QIB_6120_SerdesCfg0_L1PwrDnC_RMASK 0x1
#define QIB_6120_SerdesCfg0_L1PwrDnD_LSB 0x4
#define QIB_6120_SerdesCfg0_L1PwrDnD_RMASK 0x1
#define QIB_6120_SerdesCfg0_ResetA_LSB 0x3
#define QIB_6120_SerdesCfg0_ResetA_RMASK 0x1
#define QIB_6120_SerdesCfg0_ResetB_LSB 0x2
#define QIB_6120_SerdesCfg0_ResetB_RMASK 0x1
#define QIB_6120_SerdesCfg0_ResetC_LSB 0x1
#define QIB_6120_SerdesCfg0_ResetC_RMASK 0x1
#define QIB_6120_SerdesCfg0_ResetD_LSB 0x0
#define QIB_6120_SerdesCfg0_ResetD_RMASK 0x1

#define QIB_6120_SerdesStat_OFFS 0x3D0
#define QIB_6120_SerdesStat_Reserved_LSB 0xC
#define QIB_6120_SerdesStat_Reserved_RMASK 0xFFFFFFFFFFFFF
#define QIB_6120_SerdesStat_BeaconDetA_LSB 0xB
#define QIB_6120_SerdesStat_BeaconDetA_RMASK 0x1
#define QIB_6120_SerdesStat_BeaconDetB_LSB 0xA
#define QIB_6120_SerdesStat_BeaconDetB_RMASK 0x1
#define QIB_6120_SerdesStat_BeaconDetC_LSB 0x9
#define QIB_6120_SerdesStat_BeaconDetC_RMASK 0x1
#define QIB_6120_SerdesStat_BeaconDetD_LSB 0x8
#define QIB_6120_SerdesStat_BeaconDetD_RMASK 0x1
#define QIB_6120_SerdesStat_RxDetA_LSB 0x7
#define QIB_6120_SerdesStat_RxDetA_RMASK 0x1
#define QIB_6120_SerdesStat_RxDetB_LSB 0x6
#define QIB_6120_SerdesStat_RxDetB_RMASK 0x1
#define QIB_6120_SerdesStat_RxDetC_LSB 0x5
#define QIB_6120_SerdesStat_RxDetC_RMASK 0x1
#define QIB_6120_SerdesStat_RxDetD_LSB 0x4
#define QIB_6120_SerdesStat_RxDetD_RMASK 0x1
#define QIB_6120_SerdesStat_TxIdleDetA_LSB 0x3
#define QIB_6120_SerdesStat_TxIdleDetA_RMASK 0x1
#define QIB_6120_SerdesStat_TxIdleDetB_LSB 0x2
#define QIB_6120_SerdesStat_TxIdleDetB_RMASK 0x1
#define QIB_6120_SerdesStat_TxIdleDetC_LSB 0x1
#define QIB_6120_SerdesStat_TxIdleDetC_RMASK 0x1
#define QIB_6120_SerdesStat_TxIdleDetD_LSB 0x0
#define QIB_6120_SerdesStat_TxIdleDetD_RMASK 0x1

#define QIB_6120_XGXSCfg_OFFS 0x3D8
#define QIB_6120_XGXSCfg_ArmLaunchErrorDisable_LSB 0x3F
#define QIB_6120_XGXSCfg_ArmLaunchErrorDisable_RMASK 0x1
#define QIB_6120_XGXSCfg_Reserved_LSB 0x17
#define QIB_6120_XGXSCfg_Reserved_RMASK 0xFFFFFFFFFF
#define QIB_6120_XGXSCfg_polarity_inv_LSB 0x13
#define QIB_6120_XGXSCfg_polarity_inv_RMASK 0xF
#define QIB_6120_XGXSCfg_link_sync_mask_LSB 0x9
#define QIB_6120_XGXSCfg_link_sync_mask_RMASK 0x3FF
#define QIB_6120_XGXSCfg_port_addr_LSB 0x4
#define QIB_6120_XGXSCfg_port_addr_RMASK 0x1F
#define QIB_6120_XGXSCfg_mdd_30_LSB 0x3
#define QIB_6120_XGXSCfg_mdd_30_RMASK 0x1
#define QIB_6120_XGXSCfg_xcv_resetn_LSB 0x2
#define QIB_6120_XGXSCfg_xcv_resetn_RMASK 0x1
#define QIB_6120_XGXSCfg_Reserved1_LSB 0x1
#define QIB_6120_XGXSCfg_Reserved1_RMASK 0x1
#define QIB_6120_XGXSCfg_tx_rx_resetn_LSB 0x0
#define QIB_6120_XGXSCfg_tx_rx_resetn_RMASK 0x1

#define QIB_6120_LBIntCnt_OFFS 0x12000

#define QIB_6120_LBFlowStallCnt_OFFS 0x12008

#define QIB_6120_TxUnsupVLErrCnt_OFFS 0x12018

#define QIB_6120_TxDataPktCnt_OFFS 0x12020

#define QIB_6120_TxFlowPktCnt_OFFS 0x12028

#define QIB_6120_TxDwordCnt_OFFS 0x12030

#define QIB_6120_TxLenErrCnt_OFFS 0x12038

#define QIB_6120_TxMaxMinLenErrCnt_OFFS 0x12040

#define QIB_6120_TxUnderrunCnt_OFFS 0x12048

#define QIB_6120_TxFlowStallCnt_OFFS 0x12050

#define QIB_6120_TxDroppedPktCnt_OFFS 0x12058

#define QIB_6120_RxDroppedPktCnt_OFFS 0x12060

#define QIB_6120_RxDataPktCnt_OFFS 0x12068

#define QIB_6120_RxFlowPktCnt_OFFS 0x12070

#define QIB_6120_RxDwordCnt_OFFS 0x12078

#define QIB_6120_RxLenErrCnt_OFFS 0x12080

#define QIB_6120_RxMaxMinLenErrCnt_OFFS 0x12088

#define QIB_6120_RxICRCErrCnt_OFFS 0x12090

#define QIB_6120_RxVCRCErrCnt_OFFS 0x12098

#define QIB_6120_RxFlowCtrlErrCnt_OFFS 0x120A0

#define QIB_6120_RxBadFormatCnt_OFFS 0x120A8

#define QIB_6120_RxLinkProblemCnt_OFFS 0x120B0

#define QIB_6120_RxEBPCnt_OFFS 0x120B8

#define QIB_6120_RxLPCRCErrCnt_OFFS 0x120C0

#define QIB_6120_RxBufOvflCnt_OFFS 0x120C8

#define QIB_6120_RxTIDFullErrCnt_OFFS 0x120D0

#define QIB_6120_RxTIDValidErrCnt_OFFS 0x120D8

#define QIB_6120_RxPKeyMismatchCnt_OFFS 0x120E0

#define QIB_6120_RxP0HdrEgrOvflCnt_OFFS 0x120E8

#define QIB_6120_IBStatusChangeCnt_OFFS 0x12140

#define QIB_6120_IBLinkErrRecoveryCnt_OFFS 0x12148

#define QIB_6120_IBLinkDownedCnt_OFFS 0x12150

#define QIB_6120_IBSymbolErrCnt_OFFS 0x12158

#define QIB_6120_PcieRetryBufDiagQwordCnt_OFFS 0x12170

#define QIB_6120_RcvEgrArray0_OFFS 0x14000

#define QIB_6120_RcvTIDArray0_OFFS 0x54000

#define QIB_6120_PIOLaunchFIFO_OFFS 0x64000

#define QIB_6120_SendPIOpbcCache_OFFS 0x64800

#define QIB_6120_RcvBuf1_OFFS 0x72000

#define QIB_6120_RcvBuf2_OFFS 0x75000

#define QIB_6120_RcvFlags_OFFS 0x77000

#define QIB_6120_RcvLookupBuf1_OFFS 0x79000

#define QIB_6120_RcvDMABuf_OFFS 0x7B000

#define QIB_6120_MiscRXEIntMem_OFFS 0x7C000

#define QIB_6120_PCIERcvBuf_OFFS 0x80000

#define QIB_6120_PCIERetryBuf_OFFS 0x82000

#define QIB_6120_PCIERcvBufRdToWrAddr_OFFS 0x84000

#define QIB_6120_PIOBuf0_MA_OFFS 0x100000
