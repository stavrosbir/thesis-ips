import matplotlib.pyplot as plt
from subprocess import check_output
from math import exp, log
import sys

density = 1.1
b = 12
points = 10
samples = 20
step = exp(0.2)
start = 100

xs = []
ys = []

L = start
for p in xrange(points):

	sum_y = 0
	
	for s in xrange(samples):
		out = check_output(['./walk', str(int(L)), str(int(density*L)), str(b)])
		y = float(out.split()[0])
		sum_y += y

	xs.append(log(L))
	ys.append(log(sum_y/samples))

	L *= step

print xs, ys

n = points

sumx = sum(xs)
sumy = sum(ys)
sumx2 = sum(map(lambda x : x*x, xs))
sumxy = sum([x*y for (x,y) in zip(xs, ys)])

a = n * sumxy - sumx * sumy
c = sumy * sumx2 - sumx * sumxy
den = n * sumx2 - sumx * sumx

print a/den, exp(c/den)

plt.plot(xs, ys, label='Samples')
plt.plot((min(xs), max(xs)), ((a*min(xs)+c)/den, (a*max(xs)+c)/den), label='Fitting')
plt.legend(loc=0)
plt.savefig('figure.png')