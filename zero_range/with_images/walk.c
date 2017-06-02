// Stavros Birmpilis
// 24/3/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define UPDATE_TIMES 0

double rand_exp(double lambda) {
	if (lambda == 0) {
		return DBL_MAX;
	} else {
		double u = rand() / (RAND_MAX + 1.0);
		return -log(1 - u) / lambda;
	}
}

double g(double b, int x) {
	if (x) {
		return 1 + b / x;
	} else {
		return 0;
	}
}

// void subtract_from_all()

void print_space(int *space, int L) {
	for (int i = 0; i < L; i++) {
		printf("%d ", space[i]);
	}
	printf("\n");
}

void zero_range(int L, int N, double b, int iterations, int frames) {

	int i, j;
	// double total_time;

	int *space;
	space = calloc(L, sizeof(int));
	double *clocks;
	clocks = calloc(L, sizeof(double));

	srand(time(NULL));

	for (i = 0; i < L; i++) {
		space[i] = N / L + (i < N % L);
		clocks[i] = rand_exp(g(b, space[i]));
	}

	// total_time = 0;
	for (i = 0; i < iterations; i++) {
		// find index of min
		double min = clocks[0];
		int index = 0;
		for (j = 1; j < L; j++) {
			if (clocks[j] < min) {
				min = clocks[j];
				index = j;
			}
		}

		// if (min == DBL_MAX) {
		// 	for (j = 0; j < L; j++) {
		// 		printf("%d %lf\n", space[j], clocks[j]);
		// 	}
		// 	printf("Error1\n");
		// 	return;
		// }
		// if (space[index] == 0) {
		// 	for (j = 0; j < L; j++) {
		// 		printf("%d %lf\n", space[j], clocks[j]);
		// 	}
		// 	printf("Error2\n");
		// 	return;
		// }


		// subtract min from all clocks
		for (j = 0; j < L; j++) {
			clocks[j] -= min;
		}
		// total_time += min;

		// remove one particle and give new time
		clocks[index] = rand_exp(g(b, --space[index]));

		// move particle
		int next = (rand() % 2) ? ((index + 1) % L) : ((index ? index : L) - 1);

#if UPDATE_TIMES
		if (space[next]) {
			clocks[next] *= (space[next] + 1.0) / space[next];
		} else {
			clocks[next] = rand_exp(g(b, 1));
		}
#else
		if (space[next] == 0) {
			clocks[next] = rand_exp(g(b, 1));
		}
#endif

		space[next]++;

		// print frame
		if (i % frames == 0) {
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

	zero_range(L, N, b, iterations, frames);

	return 0;
}