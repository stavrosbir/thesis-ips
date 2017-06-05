// Stavros Birmpilis
// 5/6/17

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

void simple_exclusion(int N, double *ret) {

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
	// printf("%d\n", current_I(total_time/2, particles, N));
	ret[0] = total_time;
	ret[1] = 1.0*current_I(total_time/2, particles, N);
}

int main(int argc, char **argv) {
	
	int i, j, N, points, samples_per_point, N_step, N_start;
	double x[100], y[100], ret[2];

	points = atoi(argv[1]);
	samples_per_point = atoi(argv[2]);
	N_step = atoi(argv[3]);
	N_start = (argc > 4) ? atoi(argv[4]) : N_step;

	N = N_start;

	for (i = 0; i < points; i++) {

		for (j = 0; j < samples_per_point; j++) {
			printf("%d\n", i*samples_per_point+j);
			simple_exclusion(N, ret);
			printf("%d %.2lf %.0lf\n", N, ret[0], ret[1]);
			x[i*samples_per_point+j] = log(ret[0]);
			y[i*samples_per_point+j] = log(ret[1]);
		}

		N *= N_step;

	}

	// least squares fitting
	int total = points * samples_per_point;
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0;
	for(i = 0; i < total; i++) {
		sumx += x[i];
		sumy += y[i];
		sumxy += x[i]*y[i];
		sumx2 += x[i]*x[i];
	}
	double a = total * sumxy - sumx * sumy,
		c = sumy * sumx2 - sumx * sumxy,
		den = total * sumx2 - sumx * sumx;
	
	printf("current_I = %lf * t^%lf\n", exp(c/den), a/den);

	// Store somewhere all the results
	FILE *f;
	f = fopen("log.out", "a");
	for(i = 1; i < argc; i++) {
		fprintf(f, "%s ", argv[i]);
	}
	fprintf(f, "; ");
	fprintf(f, "current_I = %lf * t^%lf\n", exp(c/den), a/den);
	fclose(f);


	return 0;
}