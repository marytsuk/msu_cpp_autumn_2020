all: 03.o Matrix.o
	g++ -o main 03.o Matrix.o
03.o: 03.cpp Matrix.h
	g++ -c 03.cpp
Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp
test:
	./main
