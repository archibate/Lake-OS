#pragma once

#define INITRD_APPS 6
extern const void *initrd_apps[INITRD_APPS + 1];
extern tcb_t initrd_thrs[INITRD_APPS];
