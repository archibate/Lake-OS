#pragma once

#include <page.h>
#include <asm.h>

#define mmu_set_pgd(pgd) io_set_cr3((ad_t) (pgd))
#define mmu_get_pgd(pgd) ((pgp_t) io_get_cr3())
#define mmu_invalidate(vir) io_invlpg(vir)

#define mmu_reflush() mmu_set_pgd(mmu_get_pgd())
