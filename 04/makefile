all: 04.o BigInt.o
	g++ -o main 04.o BigInt.o
03.o: 04.cpp BigInt.h
	g++ -c 04.cpp
Matrix.o: BigInt.cpp BigInt.h
	g++ -c BigInt.cpp
test:
	./main
