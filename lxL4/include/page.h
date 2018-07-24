#pragma once

#define PGSIZE 0x1000

#define PGMASK 0xfffff000
#define PG_P 0x001
#define PG_W 0x002
#define PG_U 0x004
#define PG_PWT 0x008
#define PG_PCD 0x010
#define PG_A 0x020
#define PG_D 0x040
#define PG_PSE 0x080
#define PG_PAT 0x080
#define PG_G 0x100
#define PG_AVL1 0x200
#define PG_AVL2 0x400
#define PG_AVL3 0x800

#include <ad_t.h>

typedef ad_t pg_t;
typedef pg_t *pgp_t;

#define PGIDX(vir) ((vir) >> 12)
#define PGT_IDX(idx) ((idx) & 0x3ff)
#define PGD_IDX(idx) ((idx) >> 10)
