from PIL import Image
from math import log10
from sys import argv


def transform_to_RGB(x):
	#big = int(round(1020 * log10(x+1) / log10(max_x+1)))
	big = int(round(765 * log10(x+1) / log10(max_x+1)))
	if big < 255:
		return (255, 255, 255-big)
	elif big < 510:
		return (255, 255-(big%255), 0)
#	elif big < 765:
#		return (255, 0, big%255)
#	elif big < 1020:
#		return (255-(big%255), 0, 255)
#	else:
#		return (0, 0, 255)
	elif big < 765:
		return (255-(big%255), 0, 0)
	else:
		return (0, 0, 0)


global max_x

infile = argv[1]
outfile = argv[2]
L = int(argv[3])
max_x = float(argv[4])/9
scale = int(argv[5]) if len(argv) > 5 else 1


f = open(infile, 'r')

listy = []
for line in f:
	listy += map(float, line.split()[:L])

f.close()

img = Image.new('RGB', (L, L))
img.putdata(map(transform_to_RGB, listy))
if scale != 1:
	img = img.resize((scale*L, scale*L))
img.save(outfile+'.png')


