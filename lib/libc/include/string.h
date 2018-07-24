#pragma once

#include "sizet.h"

void *memset(void *dst, int val, size_t size);
void *memcpy(void *dst, const void *src, size_t size);
void *memcpy_r(void *dst, const void *src, size_t size);
void *memmove(void *dst, const void *src, size_t size);
int memcmp(const void *dst, const void *src, size_t size);
void *memchr(const void *str, int c, size_t size);
// TODO: str*** functions
