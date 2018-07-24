#pragma once

#include <page.h>

void v_map(ad_t vir, ad_t phy, unsigned attr);
int v_unmap(ad_t vir);
int v_has_vpde(ad_t vir);
pg_t v_get_mapping(ad_t vir);
void v_alloc_map_pages(ad_t pos, int count, unsigned attr);
void v_free_unmap_pages(ad_t pos, int count);
