// Copyright 2022 Alexandru Alin-Ioan 312CA
#include <stdio.h>
#include <stdlib.h>
#define NMAX 1000

// determines the coloumn letters
void det_column(int j, char *col)
{
	if (j < 26) {
		col[0] = j + 'A';
	} else if (j <= 26 * 26) {
		col[0] = j / 26 - 1 + 'A';
		col[1] = j % 26 + 'A';
	} else {
		col[0] = j / 26 / 26 - 1 + 'A';
		col[1] = (j / 26) % 26 + 'A';
		col[2] = j % 26 + 'A';
	}
}

// calculates the next position the chess piece will be moved at
int next_pos(int i, int n, int val)
{
	int pos = i;
	if (i + val >= n) {
		if (i + val % n >= n)
			pos = i + val % n - n;
		else
			pos += val % n;
	} else if (i + val < 0) {
		if (i + val % n < 0)
			pos = i + val % n + n;
		else
			pos += val % n;
	} else {
		pos += val;
	}
	return pos;
}

int main(void)
{
	int a[NMAX][NMAX] = {0}, i, j, n, val;
	long distance = 0;
	char col[3];
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	}

	// we move around the board with this
	i = 0;
	j = 0;
	while (a[i][j]) {
		val = a[i][j];
		distance += abs(val);
		a[i][j] = 0;
		if ((i + j) % 2 == 0)
			j = next_pos(j, n, val);
		else
			i = next_pos(i, n, val);
	}
	det_column(j, col);
	printf("%ld\n%d %s\n", distance, n - i, col);
}

// how does the horsie move in chess???
