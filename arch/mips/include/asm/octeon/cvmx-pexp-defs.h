/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2011 Cavium Networks
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a different license from Cavium.
 * Contact Cavium Networks for more information
 ***********************license end**************************************/

#ifndef __CVMX_PEXP_DEFS_H__
#define __CVMX_PEXP_DEFS_H__

#define CVMX_PEXP_NPEI_BAR1_INDEXX(offset) (CVMX_ADD_IO_SEG(0x00011F0000008000ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011F0000008580ull))
#define CVMX_PEXP_NPEI_BIST_STATUS2 (CVMX_ADD_IO_SEG(0x00011F0000008680ull))
#define CVMX_PEXP_NPEI_CTL_PORT0 (CVMX_ADD_IO_SEG(0x00011F0000008250ull))
#define CVMX_PEXP_NPEI_CTL_PORT1 (CVMX_ADD_IO_SEG(0x00011F0000008260ull))
#define CVMX_PEXP_NPEI_CTL_STATUS (CVMX_ADD_IO_SEG(0x00011F0000008570ull))
#define CVMX_PEXP_NPEI_CTL_STATUS2 (CVMX_ADD_IO_SEG(0x00011F000000BC00ull))
#define CVMX_PEXP_NPEI_DATA_OUT_CNT (CVMX_ADD_IO_SEG(0x00011F00000085F0ull))
#define CVMX_PEXP_NPEI_DBG_DATA (CVMX_ADD_IO_SEG(0x00011F0000008510ull))
#define CVMX_PEXP_NPEI_DBG_SELECT (CVMX_ADD_IO_SEG(0x00011F0000008500ull))
#define CVMX_PEXP_NPEI_DMA0_INT_LEVEL (CVMX_ADD_IO_SEG(0x00011F00000085C0ull))
#define CVMX_PEXP_NPEI_DMA1_INT_LEVEL (CVMX_ADD_IO_SEG(0x00011F00000085D0ull))
#define CVMX_PEXP_NPEI_DMAX_COUNTS(offset) (CVMX_ADD_IO_SEG(0x00011F0000008450ull) + ((offset) & 7) * 16)
#define CVMX_PEXP_NPEI_DMAX_DBELL(offset) (CVMX_ADD_IO_SEG(0x00011F00000083B0ull) + ((offset) & 7) * 16)
#define CVMX_PEXP_NPEI_DMAX_IBUFF_SADDR(offset) (CVMX_ADD_IO_SEG(0x00011F0000008400ull) + ((offset) & 7) * 16)
#define CVMX_PEXP_NPEI_DMAX_NADDR(offset) (CVMX_ADD_IO_SEG(0x00011F00000084A0ull) + ((offset) & 7) * 16)
#define CVMX_PEXP_NPEI_DMA_CNTS (CVMX_ADD_IO_SEG(0x00011F00000085E0ull))
#define CVMX_PEXP_NPEI_DMA_CONTROL (CVMX_ADD_IO_SEG(0x00011F00000083A0ull))
#define CVMX_PEXP_NPEI_DMA_PCIE_REQ_NUM (CVMX_ADD_IO_SEG(0x00011F00000085B0ull))
#define CVMX_PEXP_NPEI_DMA_STATE1 (CVMX_ADD_IO_SEG(0x00011F00000086C0ull))
#define CVMX_PEXP_NPEI_DMA_STATE1_P1 (CVMX_ADD_IO_SEG(0x00011F0000008680ull))
#define CVMX_PEXP_NPEI_DMA_STATE2 (CVMX_ADD_IO_SEG(0x00011F00000086D0ull))
#define CVMX_PEXP_NPEI_DMA_STATE2_P1 (CVMX_ADD_IO_SEG(0x00011F0000008690ull))
#define CVMX_PEXP_NPEI_DMA_STATE3_P1 (CVMX_ADD_IO_SEG(0x00011F00000086A0ull))
#define CVMX_PEXP_NPEI_DMA_STATE4_P1 (CVMX_ADD_IO_SEG(0x00011F00000086B0ull))
#define CVMX_PEXP_NPEI_DMA_STATE5_P1 (CVMX_ADD_IO_SEG(0x00011F00000086C0ull))
#define CVMX_PEXP_NPEI_INT_A_ENB (CVMX_ADD_IO_SEG(0x00011F0000008560ull))
#define CVMX_PEXP_NPEI_INT_A_ENB2 (CVMX_ADD_IO_SEG(0x00011F000000BCE0ull))
#define CVMX_PEXP_NPEI_INT_A_SUM (CVMX_ADD_IO_SEG(0x00011F0000008550ull))
#define CVMX_PEXP_NPEI_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000008540ull))
#define CVMX_PEXP_NPEI_INT_ENB2 (CVMX_ADD_IO_SEG(0x00011F000000BCD0ull))
#define CVMX_PEXP_NPEI_INT_INFO (CVMX_ADD_IO_SEG(0x00011F0000008590ull))
#define CVMX_PEXP_NPEI_INT_SUM (CVMX_ADD_IO_SEG(0x00011F0000008530ull))
#define CVMX_PEXP_NPEI_INT_SUM2 (CVMX_ADD_IO_SEG(0x00011F000000BCC0ull))
#define CVMX_PEXP_NPEI_LAST_WIN_RDATA0 (CVMX_ADD_IO_SEG(0x00011F0000008600ull))
#define CVMX_PEXP_NPEI_LAST_WIN_RDATA1 (CVMX_ADD_IO_SEG(0x00011F0000008610ull))
#define CVMX_PEXP_NPEI_MEM_ACCESS_CTL (CVMX_ADD_IO_SEG(0x00011F00000084F0ull))
#define CVMX_PEXP_NPEI_MEM_ACCESS_SUBIDX(offset) (CVMX_ADD_IO_SEG(0x00011F0000008280ull) + ((offset) & 31) * 16 - 16*12)
#define CVMX_PEXP_NPEI_MSI_ENB0 (CVMX_ADD_IO_SEG(0x00011F000000BC50ull))
#define CVMX_PEXP_NPEI_MSI_ENB1 (CVMX_ADD_IO_SEG(0x00011F000000BC60ull))
#define CVMX_PEXP_NPEI_MSI_ENB2 (CVMX_ADD_IO_SEG(0x00011F000000BC70ull))
#define CVMX_PEXP_NPEI_MSI_ENB3 (CVMX_ADD_IO_SEG(0x00011F000000BC80ull))
#define CVMX_PEXP_NPEI_MSI_RCV0 (CVMX_ADD_IO_SEG(0x00011F000000BC10ull))
#define CVMX_PEXP_NPEI_MSI_RCV1 (CVMX_ADD_IO_SEG(0x00011F000000BC20ull))
#define CVMX_PEXP_NPEI_MSI_RCV2 (CVMX_ADD_IO_SEG(0x00011F000000BC30ull))
#define CVMX_PEXP_NPEI_MSI_RCV3 (CVMX_ADD_IO_SEG(0x00011F000000BC40ull))
#define CVMX_PEXP_NPEI_MSI_RD_MAP (CVMX_ADD_IO_SEG(0x00011F000000BCA0ull))
#define CVMX_PEXP_NPEI_MSI_W1C_ENB0 (CVMX_ADD_IO_SEG(0x00011F000000BCF0ull))
#define CVMX_PEXP_NPEI_MSI_W1C_ENB1 (CVMX_ADD_IO_SEG(0x00011F000000BD00ull))
#define CVMX_PEXP_NPEI_MSI_W1C_ENB2 (CVMX_ADD_IO_SEG(0x00011F000000BD10ull))
#define CVMX_PEXP_NPEI_MSI_W1C_ENB3 (CVMX_ADD_IO_SEG(0x00011F000000BD20ull))
#define CVMX_PEXP_NPEI_MSI_W1S_ENB0 (CVMX_ADD_IO_SEG(0x00011F000000BD30ull))
#define CVMX_PEXP_NPEI_MSI_W1S_ENB1 (CVMX_ADD_IO_SEG(0x00011F000000BD40ull))
#define CVMX_PEXP_NPEI_MSI_W1S_ENB2 (CVMX_ADD_IO_SEG(0x00011F000000BD50ull))
#define CVMX_PEXP_NPEI_MSI_W1S_ENB3 (CVMX_ADD_IO_SEG(0x00011F000000BD60ull))
#define CVMX_PEXP_NPEI_MSI_WR_MAP (CVMX_ADD_IO_SEG(0x00011F000000BC90ull))
#define CVMX_PEXP_NPEI_PCIE_CREDIT_CNT (CVMX_ADD_IO_SEG(0x00011F000000BD70ull))
#define CVMX_PEXP_NPEI_PCIE_MSI_RCV (CVMX_ADD_IO_SEG(0x00011F000000BCB0ull))
#define CVMX_PEXP_NPEI_PCIE_MSI_RCV_B1 (CVMX_ADD_IO_SEG(0x00011F0000008650ull))
#define CVMX_PEXP_NPEI_PCIE_MSI_RCV_B2 (CVMX_ADD_IO_SEG(0x00011F0000008660ull))
#define CVMX_PEXP_NPEI_PCIE_MSI_RCV_B3 (CVMX_ADD_IO_SEG(0x00011F0000008670ull))
#define CVMX_PEXP_NPEI_PKTX_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F000000A400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_INSTR_BADDR(offset) (CVMX_ADD_IO_SEG(0x00011F000000A800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_INSTR_BAOFF_DBELL(offset) (CVMX_ADD_IO_SEG(0x00011F000000AC00ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_INSTR_FIFO_RSIZE(offset) (CVMX_ADD_IO_SEG(0x00011F000000B000ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_INSTR_HEADER(offset) (CVMX_ADD_IO_SEG(0x00011F000000B400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_IN_BP(offset) (CVMX_ADD_IO_SEG(0x00011F000000B800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_SLIST_BADDR(offset) (CVMX_ADD_IO_SEG(0x00011F0000009400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_SLIST_BAOFF_DBELL(offset) (CVMX_ADD_IO_SEG(0x00011F0000009800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKTX_SLIST_FIFO_RSIZE(offset) (CVMX_ADD_IO_SEG(0x00011F0000009C00ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKT_CNT_INT (CVMX_ADD_IO_SEG(0x00011F0000009110ull))
#define CVMX_PEXP_NPEI_PKT_CNT_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000009130ull))
#define CVMX_PEXP_NPEI_PKT_DATA_OUT_ES (CVMX_ADD_IO_SEG(0x00011F00000090B0ull))
#define CVMX_PEXP_NPEI_PKT_DATA_OUT_NS (CVMX_ADD_IO_SEG(0x00011F00000090A0ull))
#define CVMX_PEXP_NPEI_PKT_DATA_OUT_ROR (CVMX_ADD_IO_SEG(0x00011F0000009090ull))
#define CVMX_PEXP_NPEI_PKT_DPADDR (CVMX_ADD_IO_SEG(0x00011F0000009080ull))
#define CVMX_PEXP_NPEI_PKT_INPUT_CONTROL (CVMX_ADD_IO_SEG(0x00011F0000009150ull))
#define CVMX_PEXP_NPEI_PKT_INSTR_ENB (CVMX_ADD_IO_SEG(0x00011F0000009000ull))
#define CVMX_PEXP_NPEI_PKT_INSTR_RD_SIZE (CVMX_ADD_IO_SEG(0x00011F0000009190ull))
#define CVMX_PEXP_NPEI_PKT_INSTR_SIZE (CVMX_ADD_IO_SEG(0x00011F0000009020ull))
#define CVMX_PEXP_NPEI_PKT_INT_LEVELS (CVMX_ADD_IO_SEG(0x00011F0000009100ull))
#define CVMX_PEXP_NPEI_PKT_IN_BP (CVMX_ADD_IO_SEG(0x00011F00000086B0ull))
#define CVMX_PEXP_NPEI_PKT_IN_DONEX_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F000000A000ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_NPEI_PKT_IN_INSTR_COUNTS (CVMX_ADD_IO_SEG(0x00011F00000086A0ull))
#define CVMX_PEXP_NPEI_PKT_IN_PCIE_PORT (CVMX_ADD_IO_SEG(0x00011F00000091A0ull))
#define CVMX_PEXP_NPEI_PKT_IPTR (CVMX_ADD_IO_SEG(0x00011F0000009070ull))
#define CVMX_PEXP_NPEI_PKT_OUTPUT_WMARK (CVMX_ADD_IO_SEG(0x00011F0000009160ull))
#define CVMX_PEXP_NPEI_PKT_OUT_BMODE (CVMX_ADD_IO_SEG(0x00011F00000090D0ull))
#define CVMX_PEXP_NPEI_PKT_OUT_ENB (CVMX_ADD_IO_SEG(0x00011F0000009010ull))
#define CVMX_PEXP_NPEI_PKT_PCIE_PORT (CVMX_ADD_IO_SEG(0x00011F00000090E0ull))
#define CVMX_PEXP_NPEI_PKT_PORT_IN_RST (CVMX_ADD_IO_SEG(0x00011F0000008690ull))
#define CVMX_PEXP_NPEI_PKT_SLIST_ES (CVMX_ADD_IO_SEG(0x00011F0000009050ull))
#define CVMX_PEXP_NPEI_PKT_SLIST_ID_SIZE (CVMX_ADD_IO_SEG(0x00011F0000009180ull))
#define CVMX_PEXP_NPEI_PKT_SLIST_NS (CVMX_ADD_IO_SEG(0x00011F0000009040ull))
#define CVMX_PEXP_NPEI_PKT_SLIST_ROR (CVMX_ADD_IO_SEG(0x00011F0000009030ull))
#define CVMX_PEXP_NPEI_PKT_TIME_INT (CVMX_ADD_IO_SEG(0x00011F0000009120ull))
#define CVMX_PEXP_NPEI_PKT_TIME_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000009140ull))
#define CVMX_PEXP_NPEI_RSL_INT_BLOCKS (CVMX_ADD_IO_SEG(0x00011F0000008520ull))
#define CVMX_PEXP_NPEI_SCRATCH_1 (CVMX_ADD_IO_SEG(0x00011F0000008270ull))
#define CVMX_PEXP_NPEI_STATE1 (CVMX_ADD_IO_SEG(0x00011F0000008620ull))
#define CVMX_PEXP_NPEI_STATE2 (CVMX_ADD_IO_SEG(0x00011F0000008630ull))
#define CVMX_PEXP_NPEI_STATE3 (CVMX_ADD_IO_SEG(0x00011F0000008640ull))
#define CVMX_PEXP_NPEI_WINDOW_CTL (CVMX_ADD_IO_SEG(0x00011F0000008380ull))
#define CVMX_PEXP_SLI_BIST_STATUS (CVMX_ADD_IO_SEG(0x00011F0000010580ull))
#define CVMX_PEXP_SLI_CTL_PORTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000010050ull) + ((offset) & 3) * 16)
#define CVMX_PEXP_SLI_CTL_STATUS (CVMX_ADD_IO_SEG(0x00011F0000010570ull))
#define CVMX_PEXP_SLI_DATA_OUT_CNT (CVMX_ADD_IO_SEG(0x00011F00000105F0ull))
#define CVMX_PEXP_SLI_DBG_DATA (CVMX_ADD_IO_SEG(0x00011F0000010310ull))
#define CVMX_PEXP_SLI_DBG_SELECT (CVMX_ADD_IO_SEG(0x00011F0000010300ull))
#define CVMX_PEXP_SLI_DMAX_CNT(offset) (CVMX_ADD_IO_SEG(0x00011F0000010400ull) + ((offset) & 1) * 16)
#define CVMX_PEXP_SLI_DMAX_INT_LEVEL(offset) (CVMX_ADD_IO_SEG(0x00011F00000103E0ull) + ((offset) & 1) * 16)
#define CVMX_PEXP_SLI_DMAX_TIM(offset) (CVMX_ADD_IO_SEG(0x00011F0000010420ull) + ((offset) & 1) * 16)
#define CVMX_PEXP_SLI_INT_ENB_CIU (CVMX_ADD_IO_SEG(0x00011F0000013CD0ull))
#define CVMX_PEXP_SLI_INT_ENB_PORTX(offset) (CVMX_ADD_IO_SEG(0x00011F0000010340ull) + ((offset) & 1) * 16)
#define CVMX_PEXP_SLI_INT_SUM (CVMX_ADD_IO_SEG(0x00011F0000010330ull))
#define CVMX_PEXP_SLI_LAST_WIN_RDATA0 (CVMX_ADD_IO_SEG(0x00011F0000010600ull))
#define CVMX_PEXP_SLI_LAST_WIN_RDATA1 (CVMX_ADD_IO_SEG(0x00011F0000010610ull))
#define CVMX_PEXP_SLI_LAST_WIN_RDATA2 (CVMX_ADD_IO_SEG(0x00011F00000106C0ull))
#define CVMX_PEXP_SLI_LAST_WIN_RDATA3 (CVMX_ADD_IO_SEG(0x00011F00000106D0ull))
#define CVMX_PEXP_SLI_MAC_CREDIT_CNT (CVMX_ADD_IO_SEG(0x00011F0000013D70ull))
#define CVMX_PEXP_SLI_MAC_CREDIT_CNT2 (CVMX_ADD_IO_SEG(0x00011F0000013E10ull))
#define CVMX_PEXP_SLI_MEM_ACCESS_CTL (CVMX_ADD_IO_SEG(0x00011F00000102F0ull))
#define CVMX_PEXP_SLI_MEM_ACCESS_SUBIDX(offset) (CVMX_ADD_IO_SEG(0x00011F00000100E0ull) + ((offset) & 31) * 16 - 16*12)
#define CVMX_PEXP_SLI_MSI_ENB0 (CVMX_ADD_IO_SEG(0x00011F0000013C50ull))
#define CVMX_PEXP_SLI_MSI_ENB1 (CVMX_ADD_IO_SEG(0x00011F0000013C60ull))
#define CVMX_PEXP_SLI_MSI_ENB2 (CVMX_ADD_IO_SEG(0x00011F0000013C70ull))
#define CVMX_PEXP_SLI_MSI_ENB3 (CVMX_ADD_IO_SEG(0x00011F0000013C80ull))
#define CVMX_PEXP_SLI_MSI_RCV0 (CVMX_ADD_IO_SEG(0x00011F0000013C10ull))
#define CVMX_PEXP_SLI_MSI_RCV1 (CVMX_ADD_IO_SEG(0x00011F0000013C20ull))
#define CVMX_PEXP_SLI_MSI_RCV2 (CVMX_ADD_IO_SEG(0x00011F0000013C30ull))
#define CVMX_PEXP_SLI_MSI_RCV3 (CVMX_ADD_IO_SEG(0x00011F0000013C40ull))
#define CVMX_PEXP_SLI_MSI_RD_MAP (CVMX_ADD_IO_SEG(0x00011F0000013CA0ull))
#define CVMX_PEXP_SLI_MSI_W1C_ENB0 (CVMX_ADD_IO_SEG(0x00011F0000013CF0ull))
#define CVMX_PEXP_SLI_MSI_W1C_ENB1 (CVMX_ADD_IO_SEG(0x00011F0000013D00ull))
#define CVMX_PEXP_SLI_MSI_W1C_ENB2 (CVMX_ADD_IO_SEG(0x00011F0000013D10ull))
#define CVMX_PEXP_SLI_MSI_W1C_ENB3 (CVMX_ADD_IO_SEG(0x00011F0000013D20ull))
#define CVMX_PEXP_SLI_MSI_W1S_ENB0 (CVMX_ADD_IO_SEG(0x00011F0000013D30ull))
#define CVMX_PEXP_SLI_MSI_W1S_ENB1 (CVMX_ADD_IO_SEG(0x00011F0000013D40ull))
#define CVMX_PEXP_SLI_MSI_W1S_ENB2 (CVMX_ADD_IO_SEG(0x00011F0000013D50ull))
#define CVMX_PEXP_SLI_MSI_W1S_ENB3 (CVMX_ADD_IO_SEG(0x00011F0000013D60ull))
#define CVMX_PEXP_SLI_MSI_WR_MAP (CVMX_ADD_IO_SEG(0x00011F0000013C90ull))
#define CVMX_PEXP_SLI_PCIE_MSI_RCV (CVMX_ADD_IO_SEG(0x00011F0000013CB0ull))
#define CVMX_PEXP_SLI_PCIE_MSI_RCV_B1 (CVMX_ADD_IO_SEG(0x00011F0000010650ull))
#define CVMX_PEXP_SLI_PCIE_MSI_RCV_B2 (CVMX_ADD_IO_SEG(0x00011F0000010660ull))
#define CVMX_PEXP_SLI_PCIE_MSI_RCV_B3 (CVMX_ADD_IO_SEG(0x00011F0000010670ull))
#define CVMX_PEXP_SLI_PKTX_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F0000012400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_INSTR_BADDR(offset) (CVMX_ADD_IO_SEG(0x00011F0000012800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_INSTR_BAOFF_DBELL(offset) (CVMX_ADD_IO_SEG(0x00011F0000012C00ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_INSTR_FIFO_RSIZE(offset) (CVMX_ADD_IO_SEG(0x00011F0000013000ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_INSTR_HEADER(offset) (CVMX_ADD_IO_SEG(0x00011F0000013400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_IN_BP(offset) (CVMX_ADD_IO_SEG(0x00011F0000013800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_OUT_SIZE(offset) (CVMX_ADD_IO_SEG(0x00011F0000010C00ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_SLIST_BADDR(offset) (CVMX_ADD_IO_SEG(0x00011F0000011400ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_SLIST_BAOFF_DBELL(offset) (CVMX_ADD_IO_SEG(0x00011F0000011800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKTX_SLIST_FIFO_RSIZE(offset) (CVMX_ADD_IO_SEG(0x00011F0000011C00ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKT_CNT_INT (CVMX_ADD_IO_SEG(0x00011F0000011130ull))
#define CVMX_PEXP_SLI_PKT_CNT_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000011150ull))
#define CVMX_PEXP_SLI_PKT_CTL (CVMX_ADD_IO_SEG(0x00011F0000011220ull))
#define CVMX_PEXP_SLI_PKT_DATA_OUT_ES (CVMX_ADD_IO_SEG(0x00011F00000110B0ull))
#define CVMX_PEXP_SLI_PKT_DATA_OUT_NS (CVMX_ADD_IO_SEG(0x00011F00000110A0ull))
#define CVMX_PEXP_SLI_PKT_DATA_OUT_ROR (CVMX_ADD_IO_SEG(0x00011F0000011090ull))
#define CVMX_PEXP_SLI_PKT_DPADDR (CVMX_ADD_IO_SEG(0x00011F0000011080ull))
#define CVMX_PEXP_SLI_PKT_INPUT_CONTROL (CVMX_ADD_IO_SEG(0x00011F0000011170ull))
#define CVMX_PEXP_SLI_PKT_INSTR_ENB (CVMX_ADD_IO_SEG(0x00011F0000011000ull))
#define CVMX_PEXP_SLI_PKT_INSTR_RD_SIZE (CVMX_ADD_IO_SEG(0x00011F00000111A0ull))
#define CVMX_PEXP_SLI_PKT_INSTR_SIZE (CVMX_ADD_IO_SEG(0x00011F0000011020ull))
#define CVMX_PEXP_SLI_PKT_INT_LEVELS (CVMX_ADD_IO_SEG(0x00011F0000011120ull))
#define CVMX_PEXP_SLI_PKT_IN_BP (CVMX_ADD_IO_SEG(0x00011F0000011210ull))
#define CVMX_PEXP_SLI_PKT_IN_DONEX_CNTS(offset) (CVMX_ADD_IO_SEG(0x00011F0000012000ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_PKT_IN_INSTR_COUNTS (CVMX_ADD_IO_SEG(0x00011F0000011200ull))
#define CVMX_PEXP_SLI_PKT_IN_PCIE_PORT (CVMX_ADD_IO_SEG(0x00011F00000111B0ull))
#define CVMX_PEXP_SLI_PKT_IPTR (CVMX_ADD_IO_SEG(0x00011F0000011070ull))
#define CVMX_PEXP_SLI_PKT_OUTPUT_WMARK (CVMX_ADD_IO_SEG(0x00011F0000011180ull))
#define CVMX_PEXP_SLI_PKT_OUT_BMODE (CVMX_ADD_IO_SEG(0x00011F00000110D0ull))
#define CVMX_PEXP_SLI_PKT_OUT_BP_EN (CVMX_ADD_IO_SEG(0x00011F0000011240ull))
#define CVMX_PEXP_SLI_PKT_OUT_ENB (CVMX_ADD_IO_SEG(0x00011F0000011010ull))
#define CVMX_PEXP_SLI_PKT_PCIE_PORT (CVMX_ADD_IO_SEG(0x00011F00000110E0ull))
#define CVMX_PEXP_SLI_PKT_PORT_IN_RST (CVMX_ADD_IO_SEG(0x00011F00000111F0ull))
#define CVMX_PEXP_SLI_PKT_SLIST_ES (CVMX_ADD_IO_SEG(0x00011F0000011050ull))
#define CVMX_PEXP_SLI_PKT_SLIST_NS (CVMX_ADD_IO_SEG(0x00011F0000011040ull))
#define CVMX_PEXP_SLI_PKT_SLIST_ROR (CVMX_ADD_IO_SEG(0x00011F0000011030ull))
#define CVMX_PEXP_SLI_PKT_TIME_INT (CVMX_ADD_IO_SEG(0x00011F0000011140ull))
#define CVMX_PEXP_SLI_PKT_TIME_INT_ENB (CVMX_ADD_IO_SEG(0x00011F0000011160ull))
#define CVMX_PEXP_SLI_PORTX_PKIND(offset) (CVMX_ADD_IO_SEG(0x00011F0000010800ull) + ((offset) & 31) * 16)
#define CVMX_PEXP_SLI_S2M_PORTX_CTL(offset) (CVMX_ADD_IO_SEG(0x00011F0000013D80ull) + ((offset) & 3) * 16)
#define CVMX_PEXP_SLI_SCRATCH_1 (CVMX_ADD_IO_SEG(0x00011F00000103C0ull))
#define CVMX_PEXP_SLI_SCRATCH_2 (CVMX_ADD_IO_SEG(0x00011F00000103D0ull))
#define CVMX_PEXP_SLI_STATE1 (CVMX_ADD_IO_SEG(0x00011F0000010620ull))
#define CVMX_PEXP_SLI_STATE2 (CVMX_ADD_IO_SEG(0x00011F0000010630ull))
#define CVMX_PEXP_SLI_STATE3 (CVMX_ADD_IO_SEG(0x00011F0000010640ull))
#define CVMX_PEXP_SLI_TX_PIPE (CVMX_ADD_IO_SEG(0x00011F0000011230ull))
#define CVMX_PEXP_SLI_WINDOW_CTL (CVMX_ADD_IO_SEG(0x00011F00000102E0ull))

#endif
