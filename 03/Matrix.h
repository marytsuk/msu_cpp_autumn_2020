#pragma once

#include <iostream>
using namespace std;

class Matrix
{
	int numRows, numColums;
	int **elem;
public:
	class Proxy
	{
	private:
		int* row, numCol;
	public:
		Proxy(int * const x, int y);
		int& operator[](int i);
		Proxy(const Proxy&);
	};
	Proxy operator[](int i) const;
	Matrix();
	Matrix(int x, int y);
	Matrix(const Matrix& obj);
	~Matrix();
	int GetNumRows() const;
	int GetNumColums() const;
	friend ostream& operator<<(ostream &out, const Matrix& obj);
	Matrix operator+(const Matrix & obj);
	Matrix& operator*=(int a);
	friend bool operator==(const Matrix& obj1, const Matrix& obj2);
	friend bool operator!=(const Matrix& obj1, const Matrix& obj2);
	Matrix& operator=(const Matrix& obj);

};