import matplotlib.pyplot as plt

def my_plot(space, label):
	freq = [0]*(max(space)+1)

	for s in space:
		freq[s] += 1

	print freq
	plt.plot(freq, label=label)

print 'hi'

space = map(int, raw_input().split())
space2 = map(int, raw_input().split())
space3 = map(int, raw_input().split())

my_plot(space, 't=0')
my_plot(space2, 't=1000')
my_plot(space3, 't=1000000')

plt.legend()
plt.savefig('figure.png')
