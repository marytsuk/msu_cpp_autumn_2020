// 05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include "MyLib.h"
#include "assert.h"
using namespace std;

int main()
{
	Data x{ 1, true, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data y{ 0, false, 0 };

	
	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	assert(err == Error::NoError);
	
	assert(x.a == y.a);
	assert(x.b == y.b);
	assert(x.c == y.c);
	cout << endl;

	std::stringstream stream1;
	stream1 << "asdfg2 ";
	stream1 << "false";
	stream1 << " 3";
	
	Data y1{ 0, false, 0 };
	Deserializer deserializer1(stream1);
	const Error err1 = deserializer1.load(y1);
	assert(err1 == Error::CorruptedArchive);
	cout << endl;

	Data y2{ 0, false, 0 };
	std::stringstream stream2;
	stream2 << "12 ";
	stream2 << "faaaalse";
	stream2 << " 22";
	
	Deserializer deserializer2(stream2);
	const Error err2 = deserializer2.load(y2);
	assert(err2 == Error::CorruptedArchive);
	cout << endl;

	Data y3{ 0, false, 0 };
	std::stringstream stream3;
	stream2 << "12 ";
	stream2 << "false";
	stream2 << " ghjk";

	Deserializer deserializer3(stream3);
	const Error err3 = deserializer2.load(y3);
	assert(err3 == Error::CorruptedArchive);

	return 0;
}



