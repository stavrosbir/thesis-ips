from os import system
from sys import argv
from datetime import datetime

L = int(argv[1])
N = int(argv[2])
iterations = int(argv[3])
frames = int(argv[4])
scale = int(argv[5]) if len(argv) > 5 else 1


timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')

system("./walk %d %d %d %d > data_%s.out" % (L, N, iterations, frames, timestamp))
system("mkdir images_%s" % timestamp)
system("python draw.py data_%s.out images_%s %d %d %d" % (timestamp, timestamp, L, N/9.0, scale))
system("ffmpeg -r 25 -pattern_type glob -i 'images_%s/*.png' -c:v copy video_%s.avi" % (timestamp, timestamp))
system("rm -rf images_%s" % timestamp)
system("rm data_%s.out" % timestamp)
system("echo 'video_%s.avi L=%d N=%d iterations=%d frames=%d scale=%d' >> video_log.out" % (timestamp, L, N, iterations, frames, scale))
