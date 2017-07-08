// Stavros Birmpilis
// 21/5/17

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

int** int_matrix(int n, int k) {
    int **mtr, *temp, i;
    temp = calloc(n*k, sizeof(int));
    mtr = calloc(n, sizeof(int*));

    for (i = 0 ; i < n; i++)
        mtr[i] = temp + i*k;

    return mtr;
}

int torus_plus(int num, int L) {
	return (num + 1) % L;
}

int torus_minus(int num, int L) {
	return num ? num - 1 : L - 1;
}

void print_space(int **space, int L) {
	int i, j, sum;
	for (i = 0; i < L; i++) {
		for (j = 0; j < L; j++) {
			sum = space[torus_minus(i, L)][torus_minus(j, L)]
				+ space[torus_minus(i, L)][j]
				+ space[torus_minus(i, L)][torus_plus(j, L)]
				+ space[i][torus_minus(j, L)]
				+ space[i][j]
				+ space[i][torus_plus(j, L)]
				+ space[torus_plus(i, L)][torus_minus(j, L)]
				+ space[torus_plus(i, L)][j]
				+ space[torus_plus(i, L)][torus_plus(j, L)];
			printf("%.3lf ", sum/9.0);
		}
		printf("\n");
	}
}

void irw(int L, int N, int stop) {

	int i, j, p, time, particles_up, particles_down, particles_left, particles_right;

	int **space, **next_space;
	space = int_matrix(L, L);
	next_space = int_matrix(L, L);
	
	srand(seed());

	//init
	space[L/2][L/2] = N;

	time = 0;
	while (time < stop) {
		for (i = 0; i < L; i++) {
			for (j = 0; j < L; j++) {
				particles_up = 0;
				particles_down = 0;
				particles_left = 0;
				particles_right = 0;
				for (p = 0; p < space[i][j]; p++) {
					// switch (rand() % 4) {
					// 	case 0:
					// 		particles_up++;
					// 		break;
					// 	case 1:
					// 		particles_down++;
					// 		break;
					// 	case 2:
					// 		particles_left++;
					// 		break;
					// 	case 3:
					// 		particles_right++;
					// 		break;
					// }
					switch (rand() % 10) {
						case 0:
						case 1:
						case 2:
						case 3:
						case 4:
							particles_up++;
							break;
						case 5:
							particles_down++;
							break;
						case 6:
							particles_left++;
							break;
						case 7:
						case 8:
						case 9:
							particles_right++;
							break;
					}
				}
				next_space[torus_minus(i, L)][j] += particles_up;
				next_space[torus_plus(i, L)][j] += particles_down;
				next_space[i][torus_minus(j, L)] += particles_left;
				next_space[i][torus_plus(j, L)] += particles_right;
			}
		}
		memcpy(space[0], next_space[0], L*L*sizeof(int));
		memset(next_space[0], 0, L*L*sizeof(int));
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