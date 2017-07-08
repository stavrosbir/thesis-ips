// Stavros Birmpilis
// 28/6/17

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

long int seed() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	double time = (tv.tv_sec)*1000 + (tv.tv_usec)/1000.0;
	return (long int) time;
}

void print_space(char *space, int L) {
	for (int i = 0; i < L; i++) {
		printf("%d ", space[i]);
	}
	printf("\n");
}

char sa(char* space, int pos) {
	return (pos>=0)?(space[pos]):(1);
}

void simple_exclusion(int N) {

	int i, index, next, position, sum, partial_sum;
	double total_time, my_dice;

	char *space;
	int *particles;
	space = calloc(10*N, sizeof(char));
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
		next = (rand() % 4)?(1):(-1);
		my_dice = (rand() / (RAND_MAX + 1.0)) * (sum-(next<0));
		partial_sum = 0;
		for (i = N-1; i >= 0; i--) {
			position = particles[i];
			if (space[position] && !sa(space, position+next)) {
			// if (space[position] && !space[position+1]) {
				partial_sum++;
				if (my_dice < partial_sum) {
					index = i;
					break;
				}
			}
		}

		if (i==-1) continue;

		total_time += 1.0/(sum-(next<0));
		// total_time += rand_exp(sum);

		// move particle

		// position = particles[index];
		// if (space[position-1]) {
		// 	sum++;
		// }
		// if (space[position+2]) {
		// 	sum--;
		// }
		// space[position] = 0;
		// space[position+1] = 1;
		// particles[index]++;
		
		position = particles[index];
		if (sa(space, position-next)) {
			sum++;
		}
		if (sa(space, position+2*next)) {
			sum--;
		}
		space[position] = 0;
		if (position+next>=0)
			space[position+next] = 1;
		particles[index] += next;
		
		// printf("%d\n", next);
		// print_space(space, 2*N);
	}
	
	printf("%lf %d\n", total_time, particles[N-1]-N);
}

int main(int argc, char **argv) {
	int N;

	N = atoi(argv[1]);

	simple_exclusion(N);

	return 0;
}
