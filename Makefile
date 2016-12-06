CC=gcc
CFLAGS=-g -I.
DEPS = user.h trans.h grafo.h
OBJ = user.o trans.o grafo.o
GTEST =-test-coverage -fprofile-arcs

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) menus_grafo.o
	gcc -o $@ $^ $(CFLAGS)

gtest: $(OBJ) GTEST.o
	g++ $(GTEST) -o $@ $^ $(CFLAGS) -lgtest
clean:
	rm -rf *o main
