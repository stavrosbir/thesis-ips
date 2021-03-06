import matplotlib.pyplot as plt
from sys import argv
from math import log10

outfile = argv[1]
L = int(argv[2])

space = map(int, raw_input().split()[:L])

# space = [sum([space[(i+j)%L] for j in range(-L/20, L/20+1)])/(L/10+1.0) for i in range(L)]

# space = map(log10, map(lambda x : x + 1, space))

plt.yscale('log')
plt.plot(space)

plt.savefig(outfile+'.png')
