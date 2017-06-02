// Stavros Birmpilis
// 22/5/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long int seed() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double time = (tv.tv_sec)*1000 + (tv.tv_usec)/1000.0;
	return (long int) time;
}

int** int_matrix(int n, int k) {
    int **mtr, *temp, i;
    temp = calloc(n*k, sizeof(int));
    mtr = calloc(n, sizeof(int*));

    for (i = 0 ; i < n; i++)
        mtr[i] = temp + i*k;

    return mtr;
}

double** double_matrix(int n, int k) {
    int i;
    double **mtr, *temp;
    temp = calloc(n*k, sizeof(double));
    mtr = calloc(n, sizeof(double*));

    for (i = 0 ; i < n; i++)
        mtr[i] = temp + i*k;

    return mtr;
}

int torus_plus(int num, int L) {
	return (num + 1) % L;
}

int torus_minus(int num, int L) {
	return num ? num - 1 : L - 1;
}

void print_space(int **space, int L) {
	int i, j, sum;
	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			// sum = space[torus_minus(i, L)][torus_minus(j, L)]
			// 	+ space[torus_minus(i, L)][j]
			// 	+ space[torus_minus(i, L)][torus_plus(j, L)]
			// 	+ space[i][torus_minus(j, L)]
			// 	+ space[i][j]
			// 	+ space[i][torus_plus(j, L)]
			// 	+ space[torus_plus(i, L)][torus_minus(j, L)]
			// 	+ space[torus_plus(i, L)][j]
			// 	+ space[torus_plus(i, L)][torus_plus(j, L)];
			// printf("%.3lf ", sum/9.0);
			printf("%d ", space[i][j]);
		}
		printf("\n");
	}
}

double g(double b, int x) {
	if (x) {
		return 1 + b / x;
	} else {
		return 0;
	}
}

void zero_range_2d(int L, int N, double b, int iterations, int frames) {

	int i, j, current_i, current_j, next_i, next_j, k, found;
	double my_dice, sum = 0, partial_sum;

	int **space;
	space = int_matrix(L, L);

	srand(seed());

	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			space[i][j] = N / (L*L) + ((i*L + j) < N % (L*L));
			sum += g(b, space[i][j]);
		}
	}

	for (k = 0; k < iterations; k++) {
		
		// choose position
		my_dice = (rand() / (RAND_MAX + 1.0)) * sum;
		partial_sum = 0;
		found = 0;
		for (i = 0; i < L; i++) {
			for (j = 0; j < L; j++) {
				partial_sum += g(b, space[i][j]);
				if (my_dice < partial_sum) {
					current_i = i;
					current_j = j;
					found = 1;
					break;
				}
			}
			if (found) break;
		}
		

		// move particle
		switch (rand() % 4) {
			case 0:
				next_i = torus_minus(current_i, L);
				next_j = current_j;
				break;
			case 1:
				next_i = torus_plus(current_i, L);
				next_j = current_j;
				break;
			case 2:
				next_i = current_i;
				next_j = torus_minus(current_j, L);
				break;
			case 3:
				next_i = current_i;
				next_j = torus_plus(current_j, L);
				break;
		}

		sum -= g(b, space[current_i][current_j]) + g(b, space[next_i][next_j]);
		space[current_i][current_j] = space[current_i][current_j] - 1;
		space[next_i][next_j] = space[next_i][next_j] + 1;
		sum += g(b, space[current_i][current_j]) + g(b, space[next_i][next_j]);

		// print frame
		if (k % frames == 0) {
			// printf("lf\n", total_time);
			print_space(space, L);
		}
	}

	// printf("lf\n", total_time);
	print_space(space, L);
}

int main(int argc, char **argv) {
	int L, N, iterations, frames;
	double b;

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	b = atof(argv[3]);
	iterations = atoi(argv[4]);
	frames = atoi(argv[5]);

	zero_range_2d(L, N, b, iterations, frames);

	return 0;
}