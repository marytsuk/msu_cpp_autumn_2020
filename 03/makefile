all: main.o Matrix.o
	g++ -o main 03.o Matrix.o
main.o: main.cpp Matrix.h
	g++ -c 03.cpp
Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp
test:
	./main
