CC=gcc
CFLAGS=-g -I.
DEPS = user.h trans.h grafo.h
OBJ = user.o trans.o grafo.o menus_grafo.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o main
