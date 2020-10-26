// 03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <assert.h>
#include <random>
#include "Matrix.h"
using namespace std;


int main()
{
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);
	assert(m.GetNumRows() == 5);
	assert(m.GetNumColums() == 3);
	
	m[1][2] = 5;
	assert(m[1][2] == 5);

	for (int i = 0; i < m.GetNumRows(); i++)
		for (int j = 0; j < m.GetNumColums(); j++)
			m[i][j] = i + j;
	cout << "Matrix m: " << endl;
	cout << m;
	cout << "Matrix m x 3: " << endl;
	m *= 3;
	for (int i = 0; i < m.GetNumRows(); i++)
		for (int j = 0; j < m.GetNumColums(); j++)
			assert(m[i][j] == (i + j) * 3);
	cout << m;

	Matrix m1(rows, cols);
	Matrix m2(rows, cols);
	assert(m1 == m2);

	Matrix m3(rows, 2);
	Matrix m4(6, cols);
	assert(m3 != m4);

	assert(m1 != m);

	Matrix m5(rows, cols);
	for (int i = 0; i < m5.GetNumRows(); i++)
		for (int j = 0; j < m5.GetNumColums(); j++)
			m5[i][j] = i + j;
	cout << "Matrix m5: " << endl;
	cout << m5;
	Matrix m6 = m + m5;
	for (int i = 0; i < m5.GetNumRows(); i++)
		for (int j = 0; j < m5.GetNumColums(); j++)
			assert(m6[i][j] == (i + j) * 4);
	cout << "Matrix m6 = m5 + m: " << endl;
	cout << m6;
	
}


