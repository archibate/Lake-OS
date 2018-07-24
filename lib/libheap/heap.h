#pragma once

struct heap_hdr {
	struct heap_hdr *prev, *next;
	unsigned int allocated : 1;
	unsigned int len : 31;
};

#define HEAP_HDR_SIZE sizeof(struct heap_hdr)
