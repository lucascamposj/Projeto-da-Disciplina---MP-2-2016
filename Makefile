all:
	gcc -g -ftest-coverage -fprofile-arcs testa_grafo.c grafo.c -o exe
run:
	./exe 

clean:
	rm -rf *o main
