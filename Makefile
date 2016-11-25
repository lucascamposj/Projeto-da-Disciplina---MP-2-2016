all:
	gcc -g menus_grafo.c grafo.c -o exe
run:
	./exe 

clean:
	rm -rf *o main
