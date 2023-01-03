// Copyright 2022 Alexandru Alin-Ioan 312CA
#include <stdio.h>
#define NMAX 400

// checks what numbers can be put on a row
void row_check(int a[][NMAX], int pos, int n)
{
	int i, app[NMAX + 1] = {0};
	for (i = 0; i < n * n; i++) {
		if (a[pos][i])
			app[a[pos][i]] = 1;
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i])
			printf("0 ");
		else
			printf("1 ");
	}
	printf("\n");
}

// checks what numbers can be put on a column
void column_check(int a[][NMAX], int pos, int n)
{
	int i, app[NMAX + 1] = {0};
	for (i = 0; i < n * n; i++) {
		if (a[i][pos])
			app[a[i][pos]] = 1;
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i])
			printf("0 ");
		else
			printf("1 ");
	}
	printf("\n");
}

// checks what numbers can be put in a square
void square_check(int a[][NMAX], int pos, int n)
{
	int new_n = pos - pos % n, new_m = n * (pos % n), i, j, app[NMAX + 1] = {0};
	for (i = new_n; i < new_n + n; i++) {
		for (j = new_m; j < new_m + n; j++) {
			if (a[i][j])
				app[a[i][j]] = 1;
		}
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i])
			printf("0 ");
		else
			printf("1 ");
	}
	printf("\n");
}

// // checks what numbers can be put at a specfic position
void position_check(int a[][NMAX], int x, int y, int n)
{
	int i, j, app[NMAX + 1] = {0}, square = (x / n) * n + (y / n) * n;
	int new_n = square - square % n, new_m = n * (square % n);
    // row check
	for (i = 0; i < n * n; i++) {
		if (a[i][y])
			app[a[i][y]] = 1;
	}
    // column check
	for (i = 0; i < n * n; i++) {
		if (a[x][i])
			app[a[x][i]] = 1;
	}
    // square check
	for (i = new_n; i < new_n + n; i++) {
		for (j = new_m; j < new_m + n; j++) {
			if (a[i][j])
				app[a[i][j]] = 1;
		}
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i])
			printf("0 ");
		else
			printf("1 ");
	}
	printf("\n");
}

// checks for reapting values on a row
int valid_row(int a[][NMAX], int n, int pos)
{
	int i, app[NMAX + 1] = {0};
	for (i = 0; i < n * n; i++) {
		if (a[pos][i])
			app[a[pos][i]]++;
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i] > 1)
			return 0;
	}
	return 1;
}

// checks for reapting values on a column
int valid_column(int a[][NMAX], int n, int pos)
{
	int i, app[NMAX + 1] = {0};
	for (i = 0; i < n * n; i++) {
		if (a[i][pos])
			app[a[i][pos]]++;
	}
	for (i = 1; i <= n * n; i++) {
		if (app[i] > 1)
			return 0;
	}
	return 1;
}

// checks the currnet state of the game
int game_check(int a[][NMAX], int n)
{
	int i, j, gaps = 0;
	for (i = 0; i < n * n; i++) {
		if (valid_row(a, n, i) == 0 || valid_column(a, n, i) == 0)
			return 1;
		for (j = 0; j < n * n; j++) {
			if (a[i][j] == 0)
				gaps = 1;
		}
	}
	if (gaps)
		return 0;
	return 2;
}

int main(void)
{
	int a[NMAX][NMAX] = {0}, n, m, i, j;
	int operation, x, y, gps, val;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n * n; i++) {
		for (j = 0; j < n * n; j++)
			scanf("%d", &a[i][j]);
	}
	for (i = 0 ; i < m; i++) {
		scanf("%d", &operation);

		// switch used for the diffrent queries
		switch (operation) {
		case 1:{
			scanf("%d", &gps);
			row_check(a, gps - 1, n);
		}
			break;
		case 2:{
			scanf("%d", &gps);
			column_check(a, gps - 1, n);
		}
			break;
		case 3:{
			scanf("%d", &gps);
			square_check(a, gps - 1, n);
		}
			break;
		case 4:{
			scanf("%d %d", &x, &y);
			if (a[x - 1][y - 1] == 0) {
				position_check(a, x - 1, y - 1, n);
			} else {
				for (j = 0; j < n * n; j++)
					printf("0 ");
				printf("\n");
			}
		}
			break;
		case 5:{
			scanf("%d %d %d", &x, &y, &val);
			if (a[x - 1][y - 1] == 0)
				a[x - 1][y - 1] = val;
		}
			break;
		case 6:{
			printf("%d\n", game_check(a, n));
		}
			break;
		default:
			break;
		}
	}
	return 0;
}

