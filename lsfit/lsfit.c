#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void linear_fit(double x[], double y[], int n, double *a, double *b) {

	int i;
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0, den;

	for (i = 0; i < n; i++) {
		sumx += x[i];
		sumy += y[i];
		sumxy += x[i]*y[i];
		sumx2 += x[i]*x[i];
	}

	den = n * sumx2 - sumx * sumx;
	if (a != NULL) {
		*a = (n * sumxy - sumx * sumy)/den;
	}
	if (b != NULL) {
		*b = (sumy * sumx2 - sumx * sumxy)/den;
	}

}

void exponential_fit(double x[], double y[], int n, double *c, double *k) {

	int i;
	double *log_x, *log_y, log_c;

	log_x = malloc(n*sizeof(double));
	log_y = malloc(n*sizeof(double));

	for (i = 0; i < n; i++) {
		log_x[i] = log(x[i]);
		log_y[i] = log(y[i]);
	}

	linear_fit(log_x, log_y, n, k, &log_c);
	if (c != NULL) {
		*c = exp(log_c);
	}

}