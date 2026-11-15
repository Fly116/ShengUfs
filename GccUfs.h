// SPDX-License-Identifier: BSD-2-Clause-Patent
// SM8550 GCC registers used by UFS, transcribed as facts from the public
// Linux gcc-sm8550.c clock driver. No write is performed by NativeUfs yet.
#ifndef NATIVE_UFS_GCC_UFS_H
#define NATIVE_UFS_GCC_UFS_H

// Physical windows from the sheng board DT (clock-controller@100000, ufshc@1d84000).
#define GCC_BASE                      0x00100000ULL
#define UFS_HC_BASE                   0x01d84000ULL
#define UFS_HC_SIZE                   0x3000ULL

#define GCC_UFS_PHY_GDSCR             0x77004
#define GCC_UFS_MEM_PHY_GDSCR         0x9e000

#define GCC_UFS_PHY_AXI_ENABLE        0x77018
#define GCC_UFS_PHY_AHB_ENABLE        0x77024
#define GCC_UFS_PHY_TX_SYMBOL0_ENABLE 0x77028
#define GCC_UFS_PHY_RX_SYMBOL0_ENABLE 0x7702c
#define GCC_UFS_PHY_UNIPRO_CORE_ENABLE 0x77068
#define GCC_UFS_PHY_ICE_CORE_ENABLE   0x77074
#define GCC_UFS_PHY_PHY_AUX_ENABLE    0x770b0
#define GCC_UFS_PHY_RX_SYMBOL1_ENABLE 0x770cc
// bus_aggr_clk in the board DT: gcc_aggre_ufs_phy_axi_clk, halt/enable 0x770e4, HW clock gating bit1
#define GCC_AGGRE_UFS_PHY_AXI_ENABLE  0x770e4

#define GCC_UFS_BRANCH_ENABLE_BIT     0x1U

// gcc_ufs_phy_ahb_clk and gcc_aggre_ufs_phy_axi_clk set hwcg_bit=1 in gcc-sm8550.c, so CLK_OFF=1 on
// an idle branch is normal (hardware 2026-10-17 read ahb=80000003).
// The reset and RPMh/TCSR/QMP-PHY programming are not represented here: their
// semantics are not qualified and NativeUfs must not write them speculatively.

// ---- liuqin (SM8475) board section -----------------------------------------------------
// Values from UniXNU-mondrian/dts/mondrian.dts, recorded as live Android measurements on
// K60, the same SM8475 SoC (2026-11). The SM8550 defines above are superseded here:
//   * UFS host window and apps SMMU base are chip-identical (0x1d84000+0x3000, 0x15000000).
//   * The UFS clock branch page on SM8475 is 0x187000 (pong,gcc-ufs-page), not
//     GCC_BASE+0x77000; branch offsets inside the page follow the K60 report list.
//   * The UFS host SMMU stream is 0xe0 (pong,smmu-stream-id), not 0x60.
//   * No UFS-MEM-PHY page has been measured on SM8475; PongUfs (working on K60) does not
//     use one. 0 means not measured: NativeUfs::inspect skips it, and nothing else
//     touches it. Do not guess it.
//   * The WiFi endpoint stream (0x1401 at GCC+0x9c900000 on SM8550) is SM8475-unmeasured;
//     the wifi=2 path stays off on liuqin until recorded.
#undef  UFS_HC_BASE
#define UFS_HC_BASE                0x01d84000ULL
#define UFS_CLK_PAGE_BASE          0x00187000ULL
#define UFS_MEM_PHY_PAGE_BASE      0ULL
#define UFS_SMMU_STREAM_ID         0xe0U
#undef  GCC_UFS_PHY_GDSCR
#define GCC_UFS_PHY_GDSCR          0x00187004ULL
#undef  GCC_UFS_PHY_AXI_ENABLE
#define GCC_UFS_PHY_AXI_ENABLE     0x00187018ULL
#undef  GCC_UFS_PHY_AHB_ENABLE
#define GCC_UFS_PHY_AHB_ENABLE     0x00187020ULL
#undef  GCC_UFS_PHY_TX_SYMBOL0_ENABLE
#define GCC_UFS_PHY_TX_SYMBOL0_ENABLE 0x00187024ULL
#undef  GCC_UFS_PHY_RX_SYMBOL0_ENABLE
#define GCC_UFS_PHY_RX_SYMBOL0_ENABLE 0x00187028ULL
#undef  GCC_UFS_PHY_UNIPRO_CORE_ENABLE
#define GCC_UFS_PHY_UNIPRO_CORE_ENABLE 0x00187064ULL
#undef  GCC_UFS_PHY_ICE_CORE_ENABLE
#define GCC_UFS_PHY_ICE_CORE_ENABLE 0x0018706cULL
#undef  GCC_UFS_PHY_PHY_AUX_ENABLE
#define GCC_UFS_PHY_PHY_AUX_ENABLE 0x001870a4ULL
#undef  GCC_UFS_PHY_RX_SYMBOL1_ENABLE
#define GCC_UFS_PHY_RX_SYMBOL1_ENABLE 0x001870c0ULL
#undef  GCC_AGGRE_UFS_PHY_AXI_ENABLE
#define GCC_AGGRE_UFS_PHY_AXI_ENABLE 0x001870d4ULL
#endif
