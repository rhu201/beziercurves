CC = gcc 

all: test.c
	$(CC) test.c bezier.c geometry.c bpt.c -o test -lglut -g -lGL -lGLU -Wall -Wextra -lm

clean:
	rm test
