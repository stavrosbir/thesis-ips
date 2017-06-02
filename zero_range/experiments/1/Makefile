FLAGS=-O3 -Wall -lm

all: walk walk_discrete walk_loop walk_loop_discrete

walk: walk.c
	gcc walk.c -o walk $(FLAGS)

walk_discrete: walk_discrete.c
	gcc walk_discrete.c -o walk_discrete $(FLAGS)

walk_loop: walk_loop.c
	gcc walk_loop.c -o walk_loop $(FLAGS)

walk_loop_discrete: walk_loop_discrete.c
	gcc walk_loop_discrete.c -o walk_loop_discrete $(FLAGS)