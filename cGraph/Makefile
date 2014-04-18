main.exe: main.o cGAlg.o cGraph.o
	gcc -o main.exe main.o cGAlg.o cGraph.o
main.o: main.c
	gcc -c -Wall main.c
cGAlg.o: cGAlg.c cGAlg.h
	gcc -g -Wall -c cGAlg.c
cGraph.o: cGraph.c cGraph.h
	gcc -g -Wall -c cGraph.c