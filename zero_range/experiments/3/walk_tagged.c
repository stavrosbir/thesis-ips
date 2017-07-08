// Stavros Birmpilis
// 14/5/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void zero_range(int L, int N, double b, int time, int class) {

	int i, current, next, move_tagged;
	double my_dice, sum, partial_sum, total_time;

	int *space;
	space = calloc(L, sizeof(int));

	srand(seed());

	// initialization with bulk
	space[0] = 3*N/4;
	int bulk_N = N - space[0],
		bulk_L = L/5,
		bulk_start = 2*L/5,
		tagged_particle = L/2;
	for (i = bulk_start; i < bulk_start + bulk_L; i++) {
		space[i] = bulk_N / bulk_L + (i < bulk_N % bulk_L + bulk_start);
	}

	sum = 0;
	for (i = 0; i < L; i++) {
		sum += g(b, space[i]);
	}

	total_time = 0;
	while (total_time < time*L*L) {

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

		total_time = rand_exp(sum);

		// move particle
		next = (rand() % 2) ? ((current + 1) % L) : ((current ? current : L) - 1);

		move_tagged = (current == tagged_particle) &&
						((class == 1) ||
						(class == 2 && space[current] == 1) ||
						(rand() % space[current] == 0));
		if (move_tagged) {
			tagged_particle = next;
		}

		sum -= g(b, space[current]) + g(b, space[next]);
		sum += g(b, --space[current]) + g(b, ++space[next]);

	}

	printf("%.3lf\n", 1.0*abs(tagged_particle - L/2)/L);

}

int main(int argc, char **argv) {
	int L, N, class, time;
	double b;

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	b = atof(argv[3]);
	time = atoi(argv[4])
	class = atoi(argv[5]);

	zero_range(L, N, b, time, class);

	return 0;
}