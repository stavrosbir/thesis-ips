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

	int i, index, position, sum, partial_sum;
	double total_time, my_dice;

	int *space, *particles;
	space = calloc(100*N, sizeof(int));
	particles = calloc(N, sizeof(int));


	srand(seed());

	// initialization
	for (i = 0; i < N; i++) {
		space[i] = 1;
		particles[i] = i;
	}

	sum = 1;
	total_time = 0;
	while (space[0]) {

		// choose position
		my_dice = (rand() / (RAND_MAX + 1.0)) * sum;
		partial_sum = 0;
		for (i = 0; i < N; i++) {
			position = particles[i];
			if (space[position] && !space[position+1]) {
				partial_sum++;
				if (my_dice < partial_sum) {
					index = i;
					break;
				}
			}
		}

		total_time += 1.0/sum;

		// move particle
		position = particles[index];
		if (space[position-1]) {
			sum++;
		}
		if (space[position+2]) {
			sum--;
		}
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