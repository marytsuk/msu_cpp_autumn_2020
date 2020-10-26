#include "Matrix.h"
#include <iomanip>
using namespace std;
Matrix::Proxy Matrix::operator [](int i) const
{
	if ((i >= numRows) || (i < 0))
		throw out_of_range("");
	Matrix::Proxy tmp(elem[i], numColums);
	return tmp;
}
Matrix::Proxy::Proxy(const Proxy& obj)
{
	row = obj.row;
	numCol = obj.numCol;
}
int& Matrix::Proxy::operator [](int i)
{
	if ((i >= numCol) || (i < 0))
		throw out_of_range("");
	return row[i];
}

Matrix::Proxy::Proxy(int * const x, int y)
{
	row = x;
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
int Matrix::GetNumRows() const
{
	return numRows;
}
int Matrix::GetNumColums() const
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
			out << setw(4) << obj.elem[i][j] << setw(4) << " ";
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
bool operator!=(const Matrix & obj1, const Matrix & obj2)
{
	if (obj1.numRows != obj2.numRows || obj1.numColums != obj2.numColums)
		return true;
	for (int i = 0; i < obj1.numRows; i++)
		for (int j = 0; j < obj2.numColums; j++)
			if (obj1.elem[i][j] != obj2.elem[i][j])
				return true;
	return false;

}
Matrix& Matrix::operator=(const Matrix& obj)
{
	Matrix tmp = obj;
	numRows = obj.numRows;
	numColums = obj.numColums;
	if (elem != nullptr)
	{
		for (int i = 0; i < numRows; i++)
		{
			delete[] elem[i];
		}
		delete[] elem;
	}
	elem = new int*[numRows];
	for (int i = 0; i < tmp.numRows; i++)
	{
		elem[i] = new int[numColums];
		for (int j = 0; j < tmp.numColums; j++)
			elem[i][j] = tmp.elem[i][j];
	}
	return *this;
}