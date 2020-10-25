// 03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <random>
using namespace std;
class Matrix
{
	int numRows, numColums;
	int **elem;
public:
	class Proxy
	{
	private:
		int* numRow, numCol;
	public:
		Proxy(int * const x, int y);
		int& operator[](int i);
		Proxy(const Proxy&);
	};
	Proxy operator[](int i);
	Matrix();
	Matrix(int x, int y);
	Matrix(const Matrix& obj);
	~Matrix();
	int GetNumRows();
	int GetNumColums();
	friend ostream& operator<<(ostream &out, const Matrix& obj);
	Matrix operator+(const Matrix & obj);
	Matrix& operator*=(int a);
	friend bool operator==(const Matrix& obj1, const Matrix& obj2);

};
Matrix::Proxy Matrix::operator [](int i)
{
	if ((i >= numRows) || (i < 0))
		throw out_of_range("");
	Matrix::Proxy tmp(elem[i], numColums);
	return tmp;
}
Matrix::Proxy::Proxy(const Proxy& obj)
{
	numRow = obj.numRow;
	numCol = obj.numCol;
}
int& Matrix::Proxy::operator [](int i)
{
	if ((i >= numCol) || (i < 0))
		throw out_of_range("");
	return numRow[i];
}

Matrix::Proxy::Proxy(int * const x, int y)
{
	numRow = x;
	numCol = y;
}
Matrix::Matrix()
{
	cin >> numRows >> numColums;
	elem = new int*[numRows];
	for (int i = 0; i < numRows; i++)
	{
		elem[i] = new int[numColums];
		for (int j = 0; j < numColums; j++)
		{
			cin >> elem[i][j];
		}
	}
}
Matrix::Matrix(int x, int y)
{
	numColums = y;
	numRows = x;
	elem = new int*[numRows];
	for (int i = 0; i < numRows; i++)
	{
		elem[i] = new int[numColums];
		for (int j = 0; j < numColums; j++)
		{
			elem[i][j] = 0;
		}
	}
}
Matrix::Matrix(const Matrix & obj)
{
	numRows = obj.numRows;
	numColums = obj.numColums;
	elem = new int*[numRows];
	for (int i = 0; i < obj.numRows; i++)
	{
		elem[i] = new int[numColums];
		for (int j = 0; j < obj.numColums; j++)
			elem[i][j] = obj.elem[i][j];
	}
}
Matrix::~Matrix()
{
	for (int i = 0; i < numRows; i++)
	{
		delete[] elem[i];
	}
	delete[] elem;
}
int Matrix::GetNumRows()
{
	return numRows;
}
int Matrix::GetNumColums()
{
	return numColums;
}
Matrix Matrix::operator+(const Matrix & obj)
{
	Matrix tmp(numRows, numColums);
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColums; j++)
		{
			tmp.elem[i][j] = elem[i][j] + obj.elem[i][j];
		}
	}
	return tmp;
	
}
Matrix& Matrix::operator*=(int a)
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColums; j++)
		{
			elem[i][j] *= a;
		}
	}
	return *this;
}

ostream & operator<<(ostream & out, const Matrix & obj)
{
	for (int i = 0; i < obj.numRows; i++)
	{
		for (int j = 0; j < obj.numColums; j++)
		{
			out << setw(4) << obj.elem[i][j] << setw(4) << " " ;
		}
		out << endl;
	}
	out << endl;
	return out;
}
bool operator==(const Matrix & obj1, const Matrix & obj2)
{
	if (obj1.numRows != obj2.numRows || obj1.numColums != obj2.numColums)
		return false;
	for (int i = 0; i < obj1.numRows; i++)
		for (int j = 0; j < obj2.numColums; j++)
			if (obj1.elem[i][j] != obj2.elem[i][j])
				return false;
	return true;

}
int main()
{
	const size_t rows = 5;
	const size_t cols = 3;

	Matrix m(rows, cols);
	assert(m.GetNumRows() == 5);
	assert(m.GetNumColums() == 3);

	m[1][2] = 5; 
	cout << "Matrix test1: " << endl;
	cout << m;
	cout << "m[1][2] = " << m[1][2] << endl;
	double x = m[4][1];
	cout << "x = " << x << endl;
	

	for (int i = 0; i < m.GetNumRows(); i++)
		for (int j = 0; j < m.GetNumColums(); j++)
			m[i][j] = 1 + rand() % 10;
	cout << endl << "Matrix test2: " << endl;
	cout << m;
	m *= 3;
	cout << endl << "Matrix mul x 3 test3: " << endl;
	cout << m;

	Matrix m1(rows, cols);
	Matrix m2(rows, cols);

	if (m1 == m2)
	{
		cout << "SUCCESS! equal" << endl;
	}
	else
		cout << "FAIL!" << endl;
	Matrix m3(rows, 2);
	Matrix m4(6, cols);

	if (m3 == m4)
	{
		cout << "FAIL!" << endl;
	}
	else
		cout << "SUCCESS! not equal" << endl;
	Matrix m5(rows, cols);
	for (int i = 0; i < m5.GetNumRows(); i++)
		for (int j = 0; j < m.GetNumColums(); j++)
			m5[i][j] = 1 + rand() % 10;

	cout << endl << "Matrix test4 m5: " << endl;
	cout << m5;

	cout << endl << "Matrix test5 m5 + m: " << endl;
	Matrix m6 = m + m5;
	cout << m6;
}


