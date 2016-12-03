CC=gcc
CFLAGS=-g -I.
DEPS = trans.h grafo.h
OBJ = trans.o grafo.o menus_grafo.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o main