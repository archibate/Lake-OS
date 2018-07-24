#include "strparse.h"
#include "string.h"

//static char nums[] = "0123456789abcdef";
static char nums[] = "0123456789ABCDEF";

char *int_to_str_f(unsigned i, char *be, int base)
{
	char *s = be;
	int n;
	do {
		n = i % base;
		i = i / base;
		*--s = nums[n];
	} while (i);
	return s;
}

char *int_to_str_f_l(unsigned i, char *be, int base, int len)
{
	memset(be - len, '0', len);
	char *s = int_to_str_f(i, be, base);
	return be - len;
}
