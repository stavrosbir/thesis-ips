// Stavros Birmpilis
// 24/3/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

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

double bulk_density(int *space, int start, int L) {
	int i, N = 0;
	for (i = start; i < start + L; i++) {
		N += space[i];
	}
	return 1.0*N/L;
}

double zero_range(int L, int N, double b) {

	int i, current, next;
	double total_time, min, clock, critical_density = 1.0/(b-2);

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

	total_time = 0;
	while (bulk_density(space, bulk_start, bulk_L) > critical_density) {

		// find index of min
		min = rand_exp(g(b, space[0]));
		current = 0;
		for (i = 1; i < L; i++) {
			clock = rand_exp(g(b, space[i]));
			if (clock < min) {
				min = clock;
				current = i;
			}
		}

		total_time += min;

		// move particle
		next = (rand() % 2) ? ((current + 1) % L) : ((current ? current : L) - 1);
		space[current]--;
		space[next]++;

	}
	
	return total_time;
}

int main(int argc, char **argv) {
	int i, j, L, N, n1, n2, stepL, n0;
	double p, b, x[100], y[100];

	p = atof(argv[1]);
	b = atof(argv[2]);
	n1 = atoi(argv[3]);
	n2 = atoi(argv[4]);
	stepL = atoi(argv[5]);
	if (argc > 6) {
		n0 = atoi(argv[6]);
	} else {
		n0 = stepL;
	}

	for (i = 0; i < n1; i++) {
		printf("%d\n", i);
		// L = (i+1)*stepL;
		L = n0*pow(stepL, i);
		printf("%d\n", L);
		N = (int) p*L;
		x[i] = log(L);
		// x[i] = L;
		y[i] = 0;
		for (j = 0; j < n2; j++) {
			y[i] += zero_range(L, N, b);
		}
		printf("%lf\n", y[i]);
		y[i] = log(y[i]/n2);
		// y[i] = y[i]/n2;
	}

	// double result;
	// exponential_fit(x, y, n1, &result, NULL);
	// printf("T_pc = L^%lf\n", result);

	// least squares fitting
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0;
	for(i = 0; i < n1; i++) {
		sumx += x[i];
		sumy += y[i];
		sumxy += x[i]*y[i];
		sumx2 += x[i]*x[i];
	}
	double a = n1 * sumxy - sumx * sumy,
		c = sumy * sumx2 - sumx * sumxy,
		den = n1 * sumx2 - sumx * sumx;
	
	printf("T_pc = L^%lf\n", a/den);

	// Store somewhere all the results
	FILE *f;
	f = fopen("log.out", "a");
	for(i = 1; i < argc; i++) {
		fprintf(f, "%s ", argv[i]);
	}
	fprintf(f, "; ");
	fprintf(f, "T_pc = L^%lf\n", a/den);
	fclose(f);

	return 0;
}