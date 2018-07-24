#include "string.h"

void *memset(void *dst, int val, size_t size)
{
	register char *cdst = dst;
	register char cval = val;
	while (size--)
		*cdst++ = cval;
	return dst;
}

void *memcpy(void *dst, const void *src, size_t size)
{
	register char *cdst = dst;
	register const char *csrc = src;
	while (size--)
		*cdst++ = *csrc++;
	return dst;
}

void *memcpy_r(void *dst, const void *src, size_t size)
{
	register char *cdst = dst;
	register const char *csrc = src;
	cdst += size;
	csrc += size;
	while (size--)
		*--cdst = *--csrc;
	return dst;
}

void *memmove(void *dst, const void *src, size_t size)
{
	if (dst < src)
		return memcpy(dst, src, size);
	else if (dst > src)
		return memcpy_r(dst, src, size);
	else
		return dst;
}

static inline int cmp(char a, char b)
{
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}

int memcmp(const void *dst, const void *src, size_t size)
{
	register const char *cdst = dst;
	register const char *csrc = src;
	register int res = 0;
	while (size--)
		if ((res = cmp(*cdst++, *csrc++)))
			break;
	return res;
}

void *memchr(const void *src, int c, size_t size)
{
	register const char *csrc = src;
	while (size--) {
		if (*csrc == c)
			return (void *) csrc;
		else
			csrc++;
	}
	return 0;
}

// TODO: add str*** functions
