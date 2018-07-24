#pragma once

#define SELFMAP_IDX 0x3ff
#define VPT_ADDR (SELFMAP_IDX << 22)
#define VPT_SIZE 0x400000
#define VPD_ADDR (VPT_ADDR + (SELFMAP_IDX << 12))
#define VPD_SIZE 0x1000

#define VPT ((pgp_t) VPT_ADDR)
#define VPD ((pgp_t) VPD_ADDR)
