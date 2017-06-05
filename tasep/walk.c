// Stavros Birmpilis
// 2/6/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

// double rand_exp(double lambda) {
// 	if (lambda == 0) {
// 		return DBL_MAX;
// 	} else {
// 		double u = rand() / (RAND_MAX + 1.0);
// 		return -log(1 - u) / lambda;
// 	}
// }

double rate_one() {
	double u = rand() / (RAND_MAX + 1.0);
	return -log(1 - u);
}

long int seed() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double time = (tv.tv_sec)*1000 + (tv.tv_usec)/1000.0;
	return (long int) time;
}

// void print_space(int *space, int L) {
// 	for (int i = 0; i < L; i++) {
// 		printf("%d ", space[i]);
// 	}
// 	printf("\n");
// }

int current_I(int x, int *particles, int N) {
	int i;
	for (i = 0; i < N; i++) {
		if (particles[i] >= x + N) {
			return N - i + 1;
		}
	}
	return 0;
}

void simple_exclusion(int N) {

	int i, index, position;
	double total_time, clock, min;

	int *space, *particles;
	space = calloc(100*N, sizeof(int));
	particles = calloc(N, sizeof(int));


	srand(seed());

	// initialization
	for (i = 0; i < N; i++) {
		space[i] = 1;
		particles[i] = i;
	}

	total_time = 0;
	while (space[0]) {

		// find index of min
		min = DBL_MAX;
		for (i = 0; i < N; i++) {
			position = particles[i];
			if (space[position] && !space[position+1]) {
				clock = rate_one();
				if (clock < min) {
					min = clock;
					index = i;
				}
			}
		}

		total_time += min;

		// move particle
		position = particles[index];
		space[position] = 0;
		space[position+1] = 1;
		particles[index]++;

	}
	
	// printf("%lf -> %d\n", total_time, particles[N-1]-N);
	printf("%d\n", current_I(total_time/2, particles, N));
}

int main(int argc, char **argv) {
	int N;

	N = atoi(argv[1]);

	simple_exclusion(N);

	return 0;
}