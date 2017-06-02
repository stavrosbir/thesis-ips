from PIL import Image
from math import log10



def transform(x):
	return (255 - int(round(log10(x+1) * 51)))


def transform_to_RGB(x):
	big = int(round(log10(x+1) * (1020/log10(2500001.0/9))))
	if big < 255:
		return (255, 255, 255-big)
	elif big < 510:
		return (255, 255-(big%255), 0)
	elif big < 765:
		return (255, 0, big%255)
	elif big < 1020:
		return (255-(big%255), 0, 255)
	else:
		return (0, 0, 255)



f = open('images.out', 'r')
L = 500

index = 0
local = 0
listy = []

for line in f:

	if local > 0 and local % L == 0:
		print index

		img = Image.new('RGB', (L, L))
		img.putdata(map(transform_to_RGB, listy))
		# img = img.resize((1000, 1000))
		img.save('images/'+("%.5d"%index)+'.png')

		index += 1
		local = 0
		listy = []

	listy += map(float, line.split()[:L])
	local += 1

f.close()
