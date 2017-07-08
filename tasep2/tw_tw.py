import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from TracyWidom import TracyWidom
from math import sqrt
import numpy as np

mean = -1.771
var = 0.8132

tw1 = TracyWidom(1)
tw2 = TracyWidom(2)
tw4 = TracyWidom(4)

start = mean - 4*sqrt(var)
step = 0.01
stop = mean + 4*sqrt(var) + step

xs = np.arange(start, stop, step)

ys1 = [tw1.pdf(x) for x in xs]
ys2 = [tw2.pdf(x) for x in xs]
ys4 = [tw4.pdf(x) for x in xs]

plt.plot(xs, ys1, label=r'$\beta=1$')
plt.plot(xs, ys2, label=r'$\beta=2$')
plt.plot(xs, ys4, label=r'$\beta=4$')
plt.legend(loc=0)
plt.savefig('tws.png')
