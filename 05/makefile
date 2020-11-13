all: 05.o 
	g++ -o main 05.o 
05.o: 05.cpp MyLib.h
	g++ -std=c++11 -c 05.cpp
test:
	./main
