#pragma once

void __attribute__((noreturn)) panic(const char *str);

#define TIMES_PANIC(n, str) \
	static int __$times__ = n; \
	if (__$times__-- <= 0) \
		panic(str);
