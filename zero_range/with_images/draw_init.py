import matplotlib.pyplot as plt

L = 1000
p_c = 0.1
p = 1


space = [p*L-p*L/5]+[0]*(2*L/5-1)+[p]*(L/5)+[0]*(2*L/5)

# space = [sum([space[(i+j)%L] for j in range(-L/20, L/20+1)])/(L/10+1.0) for i in range(L)]

# space = map(log10, map(lambda x : x + 1, space))

plt.yscale('log')
plt.plot(space)

plt.savefig('space3.png')
