execute: main.o maze.o
	g++ -g main.o maze.o -o execute

main.o: main.cpp maze.h
	g++ -g -c main.cpp

maze.o: maze.cpp maze.h
	g++ -g -c maze.cpp

clean:
	rm -f *.o execute
