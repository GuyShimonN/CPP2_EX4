all: tree

tree: main.o
	g++ -o tree main.o -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

clean:
	rm -f *.o tree
