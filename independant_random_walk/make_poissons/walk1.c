// Stavros Birmpilis
// 26/6/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

long int seed() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double time = (tv.tv_sec)*1000 + (tv.tv_usec)/1000.0;
	return (long int) time;
}

int poisson(double a) {
	int i;
	double sum = 0,
		val = exp(-a),
		u = rand() / (RAND_MAX + 1.0);
	for (i = 0; sum<u; i++) {
		sum += val;
		val *= a/(i+1);
	}
	return i;
}

int torus_plus(int num, int L) {
	return (num + 1) % L;
}

int torus_minus(int num, int L) {
	return num ? num - 1 : L - 1;
}

void print_space(int *space, int L) {
	int i;
	for (i = 0; i < L; i++) {
		printf("%d ", space[i]);
	}
	printf("\n");
}

void irw(int L, int N, int stop) {

	int i, p, time, particles_left, particles_right;

	int *space, *next_space;
	space = calloc(L, sizeof(int));
	next_space = calloc(L, sizeof(int));
	
	srand(seed());

	// init with one
	// space[L/2] = N;
	
	// init poisson
	for (i = 0; i < L; i++) {
		space[i] = poisson(1.0*N/L);
	}

	// init uniform
	// for (i = 0; i < L; i++) {
	// 	// space[i] = rand() % (2*N/L);
	// 	space[i] = N/L;
	// }

	print_space(space, L);

	time = 0;
	while (time < stop) {
		if (time==1000)
			print_space(space, L);
		for (i = 0; i < L; i++) {
			particles_left = 0;
			particles_right = 0;
			for (p = 0; p < space[i]; p++) {
				if (rand() % 2)
					particles_left++;
				else
					particles_right++;
			}
			next_space[torus_minus(i, L)] += particles_left;
			next_space[torus_plus(i, L)] += particles_right;
		}
		memcpy(space, next_space, L*sizeof(int));
		memset(next_space, 0, L*sizeof(int));
		time++;
	}
	print_space(space, L);
}

int main(int argc, char **argv) {
	int L, N, stop;

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	stop = atoi(argv[3]);

	irw(L, N, stop);

	return 0;
}