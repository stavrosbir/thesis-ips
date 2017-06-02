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

double bulk_density(int *space, int start, int L) {
	int i, N = 0;
	for (i = start; i < start + L; i++) {
		N += space[i];
	}
	return 1.0*N/L;
}

void zero_range(int L, int N, double b) {

	int i, current, next;
	long long int total_time;
	double my_dice, sum, partial_sum, critical_density = 1.0/(b-2);

	int *space;
	space = calloc(L, sizeof(int));

	srand(seed());

	// initialization with bulk
	space[0] = 3*N/4;
	int bulk_N = N - space[0],
		bulk_L = L/5,
		bulk_start = 2*L/5;
	for (i = bulk_start; i < bulk_start + bulk_L; i++) {
		space[i] = bulk_N / bulk_L + (i < bulk_N % bulk_L + bulk_start);
	}

	sum = 0;
	for (i = 0; i < L; i++) {
		sum += g(b, space[i]);
	}

	total_time = 0;
	while (bulk_density(space, bulk_start, bulk_L) > critical_density) {
		
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
		total_time++;

	}
	
	printf("%lld\n", total_time);
	// print_space(space, L);
}

int main(int argc, char **argv) {
	int L, N;
	double b;

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	b = atof(argv[3]);

	zero_range(L, N, b);

	return 0;
}