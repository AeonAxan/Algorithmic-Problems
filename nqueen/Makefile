
CFLAGS = -std=c99 -Werror -Wall

CC = clang

nq: nq.c
	$(CC) $(CFLAGS) -ggdb -o nq nq.c

nqopt: nq.c
	$(CC) $(CFLAGS) -O3 -o nq nq.c

clean:
	rm -rf *~ nq