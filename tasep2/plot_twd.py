import matplotlib.pyplot as plt
from subprocess import check_output
from math import exp, log, sqrt
import sys

def exp_fitting(xs, ys, n):

	sumx = sum(xs)
	sumy = sum(ys)
	sumx2 = sum(map(lambda x : x*x, xs))
	sumxy = sum([x*y for (x, y) in zip(xs, ys)])

	a = n * sumxy - sumx * sumy
	c = sumy * sumx2 - sumx * sumxy
	den = n * sumx2 - sumx * sumx

	return (a/den, exp(c/den))


# fitting parameters
points = 20
samples = 10
step = exp(0.25)
start = 150

# distribution parameters
iterations = 100000
particles = 100

xs = []
ys = []

# Experimenting
N = start
for p in xrange(points):
	sys.stdout.write("\r%d%%" % (100*p/points))
	sys.stdout.flush()

	sum_x = 0
	sum_y = 0
	
	for s in xrange(samples):
		out = check_output(['./walk', str(int(N))])
		(x, y) = map(float, out.split()[:2])
		# print x, y
		sum_x += x
		sum_y += y

	xs.append(sum_x/samples)
	ys.append(sum_y/samples)

	N *= step

print '\r100%'

# print xs, ys

# Fitting
# n = points * samples
n = points

log_xs = map(log, xs)
log_ys = map(log, ys)

(mean_exponent, mean_factor) = exp_fitting(log_xs, log_ys, n)
print (mean_exponent, mean_factor)

var_ys = [(y-mean_factor*x**mean_exponent)**2 for (x, y) in zip(xs, ys)]

log_var_ys = map(log, var_ys)

(var_exponent, var_factor) = exp_fitting(log_xs, log_var_ys, n)
print (var_exponent/2, sqrt(var_factor))

# Plotting
plt.plot(log_xs, log_ys, label='Samples')
plt.plot((min(log_xs), max(log_xs)), (mean_exponent*min(log_xs)+log(mean_factor), mean_exponent*max(log_xs)+log(mean_factor)), label='Fitting')
plt.legend(loc=0)
plt.savefig('figure1s.png')
plt.clf()

plt.plot(log_xs, map(lambda x : x/2, log_var_ys), label='Samples')
plt.plot((min(log_xs), max(log_xs)), (var_exponent*min(log_xs)/2+log(var_factor)/2, var_exponent*max(log_xs)/2+log(var_factor)/2), label='Fitting')
plt.legend(loc=0)
plt.savefig('figure2s.png')
plt.clf()

sys.exit(0)

# tracy widom
xs = []
ys = []

# Experimenting
for i in xrange(iterations):
	sys.stdout.write("\r%d%%" % (100*i/iterations))
	sys.stdout.flush()

	out = check_output(['./walk', str(particles)])
	(x, y) = map(float, out.split()[:2])

	xs.append(x)
	ys.append(y)

print '\r100%'

distribution = [(y-mean_factor*x**mean_exponent)/(sqrt(var_factor)*x**(var_exponent/2)) for (x, y) in zip(xs, ys)]
samples = len(distribution)
mean = sum(distribution)/samples
var = sum(map(lambda x : (x-mean)**2, distribution))/(samples-1)
skew = (sum(map(lambda x : (x-mean)**3, distribution))/samples)/(sqrt(var)**3)
kurt = (sum(map(lambda x : (x-mean)**4, distribution))/samples)/(var**2)
print mean, var, skew, (kurt-3)

plt.hist(distribution, bins=200, histtype='step', color='red', normed=True)
plt.savefig('figure3s.png')