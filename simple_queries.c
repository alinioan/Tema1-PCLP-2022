// Copyright 2022 Alexandru Alin-Ioan 312CA
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LETTERS 26

void swap_longs(long *x, long *y)
{
	long temp = *x;
	*x = *y;
	*y = temp;
}

// checks if the charater is a valid query
int valid_input(char c)
{
	if ((c >= 'a' && c <= 'z') || c == 'Q' || c == 'E' || c == 'T')
		return 1;
	return 0;
}

// gcd = greates common denominator
int gcd(int a, int b)
{
	int r;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

// searches for the letter that has the highest frequency
int max_freq(long freq[])
{
	int i, pos_max;
	long f_max = 0;
	for (i = 0; i < MAX_LETTERS; i++) {
		if (freq[i] > f_max) {
			pos_max = i;
			f_max = freq[i];
		}
	}
	return pos_max;
}

// determines when to print an alert and what the alert should be
void alert_check(int *alert_timer, long *freq, long let_cnt)
{
	int pos_maxf;
	long simplify;
	if (*alert_timer > 1) {
		(*alert_timer)--;
	} else {
		pos_maxf = max_freq(freq);
		if (freq[pos_maxf] * 2 >= let_cnt) {
			*alert_timer = 5;
			simplify = gcd(freq[pos_maxf], let_cnt);
			printf("%c ", (char)(pos_maxf + 'a'));
			printf("%ld/", freq[pos_maxf] / simplify);
			printf("%ld\n", let_cnt / simplify);
		}
	}
}

// solves the T query
void caseT(long freq[], long k)
{
	long aux[MAX_LETTERS] = {0}, chr_pos[MAX_LETTERS], i, j;

	// initialize the array with the character numbers
	for (i = 0 ; i < MAX_LETTERS; i++) {
		aux[i] = freq[i];
		chr_pos[i] = i;
	}

	// sorts the character number array according to the character frequency
	for (i = 0 ; i < MAX_LETTERS - 1; i++) {
		for (j = i + 1; j < MAX_LETTERS; j++) {
			if (aux[i] >= aux[j]) {
				swap_longs(&aux[i], &aux[j]);
				swap_longs(&chr_pos[i], &chr_pos[j]);
			}
		}
	}
	for (i = MAX_LETTERS - 1; i > MAX_LETTERS - k; i--)
		printf("%c ", (char)(chr_pos[i] + 'a'));
	printf("%c\n", (char)(chr_pos[i] + 'a'));
}

int main(void)
{
	long freq[MAX_LETTERS] = {0}, let_cnt = 0;
	int k_imp, alert_timer = 5;
	char *c;
	size_t c_size = 0;
	getline(&c, &c_size, stdin);
	while (valid_input(c[0])) {
		// switch used for the diffrent queries
		switch (c[0]) {
		case 'Q':{
				printf("%c %ld\n", c[2], freq[(int)(c[2] - 'a')]);
			}
			break;
		case 'T':{
				if (c[3] >= '0' && c[3] <= '9')
					k_imp = (int)(c[2] - '0') * 10 + (int)(c[3] - '0');
				else
					k_imp = (int)(c[2] - '0');
				caseT(freq, k_imp);
			}
			break;
		case 'E':{
				let_cnt -= freq[(int)(c[2] - 'a')];
				freq[(int)(c[2] - 'a')] = 0;
			}
			break;
		default:{
				let_cnt++;
				if (c[0] >= 'a' && c[0] <= 'z')
					freq[(int)(c[0] - 'a')]++;
				alert_check(&alert_timer, freq, let_cnt);
			}
			break;
		}
		getline(&c, &c_size, stdin);
	}
	return 0;
}
