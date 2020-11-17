// 06.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <assert.h>
#include "MyLib.h"

using namespace std;

string test_ex1()
{
	try
	{
		string str = format("{0", 1);
	}
	catch (runtime_error Ex)
	{
		return Ex.what();
	}
}
string test_ex2()
{
	try
	{
		string str = format("{0}, {1}, {5}", 1, 1);
	}
	catch (runtime_error Ex)
	{
		return Ex.what();
	}
}
string test_ex3()
{
	try
	{
		string str = format("{ccccc}, {1}, {5}", 1, 1, 1);
	}
	catch (runtime_error Ex)
	{
		return Ex.what();
	}
}
int main()
{
	string str1 = format("just a string");
	assert(str1 == "just a string");

	string str2 = format("{0} + {0} = {1}", "two", "four");
	assert(str2 == "two + two = four");

	string str3 = format("c + 1 = {0}; 1 + 2 = {1}; 10 + 5 = {2}; 2 + 1 = {3};", 'd', 3, 15, MyData(1, 2));
	assert(str3 == "c + 1 = d; 1 + 2 = 3; 10 + 5 = 15; 2 + 1 = 1+2;");

	string str4 = test_ex1();
	assert(str4 == "Invalid bracket sequence!\n");

	string str5 = test_ex2();
	assert(str5 == "Invalid number of arguments!\n");

	string str6 = test_ex3();
	assert(str6 == "Invalid format of parameter!\n");
		
	return 0;
}

