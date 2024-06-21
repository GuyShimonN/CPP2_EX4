all: test

test: test_tree.o
	g++ -o test test_tree.o -std=c++11

test_tree.o: test_tree.cpp
	g++ -c test_tree.cpp -std=c++11

clean:
	rm -f *.o test
