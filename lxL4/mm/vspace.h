#pragma once

#include <page.h>

typedef struct vspace {
	pgp_t pgd;
	ad_t brk;
} vspace_t;

void vspace_init(vspace_t *vs);
void vspace_switch(vspace_t *vs);

extern vspace_t *curvs;
