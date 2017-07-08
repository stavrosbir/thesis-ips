import matplotlib.pyplot as plt
from subprocess import check_output
from math import exp, log

points = 10
samples = 10
step = exp(0.2)
start = 150

xs = []
ys = []

N = start
for p in xrange(points):

	# sum_x = 0
	# sum_y = 0
	
	for s in xrange(samples):
		out = check_output(['./walk', str(int(N))])
		(x, y) = map(float, out.split()[:2])
		# sum_x += x
		# sum_y += y
		xs.append(log(x))
		ys.append(log(y))

	# xs.append(log(sum_x/samples))
	# ys.append(log(sum_y/samples))

	N *= step

print xs, ys

n = points * samples
# n = points

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
plt.legend(loc=2)
plt.savefig('figure.png')