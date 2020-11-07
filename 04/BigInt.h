#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class BigInt
{
	int size = 0;
	int capacity = 4;
	int* digits = nullptr;
	bool isNegative = false;
public:

	BigInt(string str);
	BigInt();
	BigInt(int a);
	BigInt(BigInt&& obj);
	~BigInt();
	BigInt(const BigInt&);
	BigInt& operator=(const BigInt&);
	BigInt& operator=(BigInt&& obj);
	

	void push(int n);
	string ReturnString() const;
	bool operator==(const BigInt&) const;
	BigInt operator-() const;
	bool operator!=(const BigInt& other) const;
	bool operator<(const BigInt& other)const;
	bool operator>(const BigInt& other)const;
	bool operator>=(const BigInt& other)const;
	bool operator<=(const BigInt& other)const;
	

	friend BigInt operator+(const BigInt&, const BigInt&);
	friend BigInt operator-(const BigInt&, const BigInt&);
	friend BigInt operator*(const BigInt&, const BigInt&);
	friend ostream& operator<<(ostream& out, const BigInt& obj);
};
