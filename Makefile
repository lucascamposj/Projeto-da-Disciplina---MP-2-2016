CC=gcc
CFLAGS=-g -I.
DEPS = user.h trans.h grafo.h
OBJ = user.o trans.o grafo.o
GTEST =-fprofile-arcs -test-coverage

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

RS: $(OBJ) rede_social.o
	gcc -o $@ $^ $(CFLAGS)

gtest:
	g++ -fprofile-arcs -ftest-coverage -g GTEST.c grafo.c trans.c user.c -o RS -lgtest

clean:
	rm -rf *o RS
