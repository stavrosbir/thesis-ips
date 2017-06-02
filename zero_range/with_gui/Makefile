all: walk walk_bulk# run

walk: walk.c simulate.py
	gcc -O3 -Wall walk.c -o walk -lm
	python simulate.py walk

walk_bulk: walk_bulk.c simulate.py
	gcc -O3 -Wall walk_bulk.c -o walk_bulk -lm
	python simulate.py walk_bulk

run: simulate.py
	python simulate.py