#pragma once

typedef struct div {
	int quot;
	int rem;
} div_t;

static inline div_t div(int m, int n)
{
	div_t res = {
		m / n,
		m % n,
	};
	return res;
}

typedef struct ldiv {
	long quot;
	long rem;
} ldiv_t;

static inline ldiv_t ldiv(long m, long n)
{
	ldiv_t res = {
		m / n,
		m % n,
	};
	return res;
}
