import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from TracyWidom import TracyWidom
from math import sqrt
import numpy as np

mean = -1.771
var = 0.8132
tw = TracyWidom()

start = mean - 3.5*sqrt(var)
step = 0.01
stop = mean + 3.5*sqrt(var) + step

xs = np.arange(start, stop, step)

ys = [tw.pdf(x) for x in xs]
bell = mlab.normpdf(xs, mean, sqrt(var))

plt.plot(xs, ys, color='orange', label='Tracy-Widom')
plt.plot(xs, bell, color='blue', label='Normal')
plt.legend(loc=0)
plt.savefig('awesome.png')
