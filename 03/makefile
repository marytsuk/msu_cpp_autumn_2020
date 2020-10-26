all: main.o Matrix.o
	g++ -o main main.o Matrix.o
main.o: main.cpp Matrix.h
	g++ -std=c++17 -c 03.cpp
Matrix.o: Matrix.cpp Matrix.h
	g++ -std=c++17 -c Matrix.cpp
test:
	./main
