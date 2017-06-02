// Stavros Birmpilis
// 30/5/17

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <float.h>

#define DISCRETE 1

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

double zero_range(int L, int N, double b, long int time, int class) {

	int i, current, next, move_tagged;
#if DISCRETE
	long int total_time;
	double my_dice, sum, partial_sum;
#else
	double total_time, min, clock;
#endif

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

#if DISCRETE
	sum = 0;
	for (i = 0; i < L; i++) {
		sum += g(b, space[i]);
	}
#endif

	total_time = 0;
	while (total_time < time*L*L) {

		// choose position
#if DISCRETE
		my_dice = (rand() / (RAND_MAX + 1.0)) * sum;
		partial_sum = 0;
		for (i = 0; i < L; i++) {
			partial_sum += g(b, space[i]);
			if (my_dice < partial_sum) {
				current = i;
				break;
			}
		}
#else
		min = rand_exp(g(b, space[0]));
		current = 0;
		for (i = 1; i < L; i++) {
			clock = rand_exp(g(b, space[i]));
			if (clock < min) {
				min = clock;
				current = i;
			}
		}
#endif

		// move particle
		next = (rand() % 2) ? ((current + 1) % L) : ((current ? current : L) - 1);

		move_tagged = (current == tagged_particle) &&
						((class == 1) ||
						(class == 2 && space[current] == 1) ||
						(rand() % space[current] == 0));
		if (move_tagged) {
			tagged_particle = next;
		}

#if DISCRETE
		sum -= g(b, space[current]) + g(b, space[next]);
		sum += g(b, --space[current]) + g(b, ++space[next]);
		total_time++;
#else
		space[current]--;
		space[next]++;
		total_time += min;
#endif

	}

	return 1.0*abs(tagged_particle - L/2)/L;

}

int main(int argc, char **argv) {
	
	int i, j, L, N, class, points, samples_per_point, time_step, time_start;
	long int time;
	double b, x[100], y[100];

	L = atoi(argv[1]);
	N = atoi(argv[2]);
	b = atof(argv[3]);
	class = atoi(argv[4]);
	points = atoi(argv[5]);
	samples_per_point = atoi(argv[6]);
	time_step = atoi(argv[7]);
	time_start = (argc > 8) ? atoi(argv[8]) : time_step;

	time = time_start;

	for (i = 0; i < points; i++) {
		printf("%d\n", i);
		
		x[i] = log(time);

		y[i] = 0;
		for (j = 0; j < samples_per_point; j++) {
			y[i] += zero_range(L, N, b, time, class);
		}
		y[i] = log(y[i]/samples_per_point);

		time *= time_step;
	}

	// least squares fitting
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0;
	for(i = 0; i < points; i++) {
		sumx += x[i];
		sumy += y[i];
		sumxy += x[i]*y[i];
		sumx2 += x[i]*x[i];
	}
	double a = points * sumxy - sumx * sumy,
		c = sumy * sumx2 - sumx * sumxy,
		den = points * sumx2 - sumx * sumx;
	
	printf("tagged_scaled = %lf * t^%lf\n", c/den, a/den);

	// Store somewhere all the results
	FILE *f;
	f = fopen("log.out", "a");
	for(i = 1; i < argc; i++) {
		fprintf(f, "%s ", argv[i]);
	}
	fprintf(f, "; ");
	fprintf(f, "tagged_scaled = %lf * t^%lf\n", c/den, a/den);
	fclose(f);

	return 0;

}