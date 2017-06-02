from PIL import Image
from math import log10


def transform(x):
	return int(round(500*log10(x+1)/log10(5001)))


f = open('zrp.out', 'r')
L = 500

index = 0
for line in f:
	print index

	space = map(transform, map(int, line.split()[:L]))

	listy = []
	for p in space:
		listy += p*[0] + (L-p)*[255]
	
	img = Image.new('L', (L, L))
	img.putdata(listy)
	img.save('images/'+("%.5d"%index)+'.png')

	index += 1

f.close()
