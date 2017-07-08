import matplotlib.pyplot as plt
from subprocess import check_output
from math import exp, log, sqrt
import sys

# (mean_exponent, mean_factor) = (0.9211270270279155, 0.9802519843506985)
# (sd_exponent, sd_factor) = (0.6145113089197869, 0.9365783464227312)
(mean_exponent, mean_factor) = (1, 0.5)
(sd_exponent, sd_factor) = (0.567, 1)

N = 100
samples = 200000
values = []

for s in xrange(samples):
	sys.stdout.write("\r%d%%" % (100*s/samples))
	sys.stdout.flush()
	out = check_output(['./walk', str(N)])
	(x, y) = map(float, out.split()[:2])
	values.append((y-mean_factor*x**mean_exponent)/(sd_factor*x**sd_exponent))
	# for t in xrange(10):
	# 	out = check_output(['./walk', str(int(N*exp(0.2*t)))])
	# 	(x, y) = map(float, out.split()[:2])
	# 	# print x, y
	# 	values.append((y-mean_factor*x**mean_exponent)/(sqrt(sd_factor)*x**(sd_exponent/2)))
	# 	# values.append((y-x)/sqrt(x))

print '\r100%'

samples = len(values)
mean = sum(values)/samples
var = sum(map(lambda x : (x-mean)**2, values))/(samples-1)
skew = (sum(map(lambda x : (x-mean)**3, values))/samples)/(sqrt(var)**3)
kurt = (sum(map(lambda x : (x-mean)**4, values))/samples)/(var**2)
print mean, var, skew, (kurt-3)


plt.hist(values, bins=200, histtype='step', color='red', normed=True)
plt.savefig('hist_twdg.png')
