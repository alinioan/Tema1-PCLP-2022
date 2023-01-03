// Copyright 2022 Alexandru Alin-Ioan 312CA
#include <stdio.h>
#include <math.h>

// determines the vector's scond largest number
void det_max(long a, long *max1, long *max2)
{
	if (a > *max1) {
		*max2 = *max1;
		*max1 = a;
	} else if (a < *max1 && a > *max2) {
		*max2 = a;
	}
}

// base 8 to base 10 converter
long cvrt_base10(long n)
{
	long dec = 0, p = 1;
	while (n) {
		dec = dec + n % 10 * p;
		n /= 10;
		p *= 8;
	}
	return dec;
}

int main(void)
{
	int n, i;
	long a_max1 = -1, a_max2 = -1, b_max1 = -1, b_max2 = -1;
	long ps = 0, a_i, b_i;
	double n_a = 0, n_b = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%ld %ld", &a_i, &b_i);
		a_i = cvrt_base10(a_i);
		b_i = cvrt_base10(b_i);
		ps += a_i * b_i;
		n_a += (double)a_i * a_i;
		n_b += (double)b_i * b_i;
		det_max(a_i, &a_max1, &a_max2);
		det_max(b_i, &b_max1, &b_max2);
	}
	printf("%ld\n%ld %ld\n", ps, a_max2, b_max2);
	printf("%.7lf %.7lf\n", sqrt(n_a), sqrt(n_b));
}

