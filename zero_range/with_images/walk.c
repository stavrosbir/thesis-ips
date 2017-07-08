// Stavros Birmpilis
// 29/5/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double g(double b, int x) {
	if (x) {
		return 1 + b / x;
	} else {
		return 0;
	}
}

long int seed() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double time = (tv.tv_sec)*1000 + (tv.tv_usec)/1000.0;
	return (long int) time;
}

void print_space(int *space, int L) {
	for (int i = 0; i < L; i++) {
		printf("%d ", space[i]);
	}
	printf("\n");
}

void zero_range(int L, int N, double b, int iterations) {

	int i, k, current, next;
	double my_dice, sum, partial_sum;

	int *space;
	space = calloc(L, sizeof(int));

	srand(seed());

	// initialization
	for (i = 0; i < L; i++) {
		space[i] = N / L + (i < N % L);
	}

	sum = 0;
	for (i = 0; i < L; i++) {
		sum += g(b, space[i]);
	}

	for (k = 0; k < iterations; k++) {
		
		// choose position
		my_dice = (rand() / (RAND_MAX + 1.0)) * sum;
		partial_sum = 0;
		for (i = 0; i < L; i++) {
			partial_sum += g(b, space[i]);
			if (my_dice < partial_sum) {
				current = i;
				break;
			}
		}

		// move particle
		next = (rand() % 2) ? ((current + 1) % L) : ((current ? current : L) - 1);
		sum -= g(b, space[current]) + g(b, space[next]);
		sum += g(b, --space[current]) + g(b, ++space[next]);

	}
	
	print_space(space, L);
}

int main(int argc, char **argv) {
	int L, N, iterations;
	double b;

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	b = atof(argv[3]);
	iterations = atoi(argv[4]);

	zero_range(L, N, b, iterations);

	return 0;
}