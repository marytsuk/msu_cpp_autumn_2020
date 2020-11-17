all: 06.o 
	g++ -o main 06.o 
06.o: 06.cpp MyLib.h
	g++ -std=c++17 -c 06.cpp
test:
	./main
