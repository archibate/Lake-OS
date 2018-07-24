#pragma once

#ifdef _LIBC_USE_BUILTIN
#define abs __builtin_abs
#define labs __builtin_labs
#else
int abs(int x)
{
	union convert {
		int x;
		unsigned u;
	} u;
	u.x = x;
	u.u &= (unsigned) INT_MAX;
	return u.x;
}

long labs(long x)
{
	union convert {
		long x;
		unsigned long u;
	} u;
	u.x = x;
	u.u &= (unsigned long) LONG_MAX;
	return u.x;
}
#endif
