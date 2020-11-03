#include "BigInt.h"
#include <string.h>
#include <algorithm>
using namespace std;
string BigInt::ReturnString()
{
	string res;
	if (isNegative)
	{
		res.push_back('-');
	}
	for (int i = 0; i < size; i++)
	{
		res.push_back((char)(digits[i] + '0'));
	}
	return res;
}
BigInt::BigInt(string str)
{
	
	digits = new int[capacity];
	if (str[0] == '-')
	{
		isNegative = true;
		str = str.substr(1);
	}
	for (int i = 0; i < str.length(); i++)
	{
		push(str[i] - '0');
	}
}
BigInt::BigInt(const BigInt& obj)
{
	int* tmp = new int[capacity];
	for (int i = 0; i < obj.size; i++)
	{
		tmp[i] = obj.digits[i];
	}
	digits = tmp;
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
}
void BigInt::push(int c)
{

	if (size < capacity)
	{
		digits[size] = c;
		size += 1;
	}
	else 
	{
		capacity *= 2;

		int* tmp = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			tmp[i] = digits[i];
		}
		
		delete[] digits;
		digits = tmp;
		digits[size] = c;
		size += 1;
	}
}
BigInt::~BigInt()
{
	if (digits != nullptr)
		delete[] digits;
}
ostream& operator<<(ostream& out, const BigInt& obj)
{
	if (obj.isNegative)
		out << "-";
	//out << "size: " << obj.size << "       ";
	for (int i = 0; i < obj.size; i++)
		out << obj.digits[i];
	return out;
}
BigInt BigInt::operator-() const
{
	BigInt tmp = *this;
	tmp.isNegative = !tmp.isNegative;
	return tmp;
}
BigInt operator+(const BigInt& obj1, const BigInt& obj2)
{
	int size_a = obj1.size - 1;
	int size_b = obj2.size - 1;
	int length = max(size_a, size_b);


	if (!obj1.isNegative && obj2.isNegative)
		return obj1 - (-obj2);

	if (obj1.isNegative && !obj2.isNegative)
		return obj2 - (-obj1);

	if (obj1.isNegative && obj2.isNegative)
		return -((-obj1) + (-obj2));
	string str = "";
	if (!obj1.isNegative && !obj2.isNegative)
	{
		BigInt res;
		res.digits = new int[length + 1];
		int carry = 0;
		res.size = length + 1;
		res.capacity = length + 1;
		res.isNegative = false;
		for (int i = length; i >= 0; i--)
		{
			if (size_a < 0)
			{
				int sum = obj2.digits[size_b];
				sum += carry;
				res.digits[i] = sum % 10;
				
				carry = sum / 10;
				size_b--;
			}
			else if (size_b < 0)
			{
				int sum = obj1.digits[size_a];
				sum += carry;
				
				res.digits[i] = sum % 10;
				carry = sum / 10;
				size_a--;
			}
			else
			{
				int sum = obj1.digits[size_a] + obj2.digits[size_b];
				sum += carry;
				res.digits[i] = sum % 10;
				
				carry = sum / 10;
				size_a--;
				size_b--;
			}
		}
		
		if (carry)
		{
			
			int* tmp = new int[length + 2];
			for (int i = 1; i < length + 2; i++)
			{
				tmp[i] = res.digits[i - 1];
			}
			tmp[0] = carry;
			delete[] res.digits;
			res.digits = tmp;
			res.size = length + 2;
			res.capacity = length + 2;
		}
		
		return res;
	}

}

bool BigInt::operator==(const BigInt& obj) const
{
	if (size != obj.size)
		return false;
	if (isNegative != obj.isNegative)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (digits[i] != obj.digits[i])
			return false;
	}
	return true;
}
bool BigInt::operator!=(const BigInt& obj) const
{
	if (size != obj.size)
		return true;
	if (isNegative != obj.isNegative)
		return true;
	
	for (int i = 0; i < size; i++)
	{
		if (digits[i] != obj.digits[i])
			return true;
	}
	return false;
}
bool BigInt::operator<=(const BigInt& obj) const
{
	if (isNegative && !obj.isNegative)
		return true;
	if (!isNegative && obj.isNegative)
		return false;
	if (isNegative && obj.isNegative)
	{
		if (size < obj.size)
			return false;
		if (size > obj.size)
			return true;

		for (int i = 0; i < size; i++)
		{
			if (digits[i] < obj.digits[i])
			{
				return false;
			}
			
		}
		return true;
	}
	if (!isNegative && !obj.isNegative)
	{
		if (size < obj.size)
			return true;
		if (size > obj.size)
			return false;

		for (int i = 0; i < size; i++)
		{
			if (digits[i] > obj.digits[i])
			{
				return false;
			}
		}
		return true;
	}
}
bool BigInt::operator>=(const BigInt& obj)const
{
	if (isNegative && !obj.isNegative)
		return false;
	if (!isNegative && obj.isNegative)
		return true;
	if (isNegative && obj.isNegative)
	{
		if (size < obj.size)
			return true;
		if (size > obj.size)
			return false;

		for (int i = 0; i < size; i++)
		{
			if (digits[i] > obj.digits[i])
			{
				return false;
			}
		}
		return true;
	}
	if (!isNegative && !obj.isNegative)
	{
		if (size < obj.size)
			return false;
		if (size > obj.size)
			return true;

		for (int i = 0; i < size; i++)
		{
			if (digits[i] < obj.digits[i])
			{
				return false;
			}
		}
		return true;
	}
}
bool BigInt::operator<(const BigInt& obj) const
{
	return ((*this) <= obj) && ((*this) != obj);
}
bool BigInt::operator>(const BigInt& other) const
{
	return ((*this) >= other) && ((*this) != other);
}
BigInt::BigInt()
{}
BigInt operator*(const BigInt& obj1, const BigInt& obj2)
{
	int size_a = obj1.size;
	int size_b = obj2.size;
	int length = size_a + size_b;
	BigInt res;
	if (!obj1.isNegative && !obj2.isNegative || obj1.isNegative && obj2.isNegative)
		res.isNegative = false;
	else
		res.isNegative = true;

	res.digits = new int[length];
	for (int i = 0; i < length; i++)
	{
		res.digits[i] = 0;
	}
	for (int i = 0; i < size_a; i++)
		for (int j = 0; j < size_b; j++)
			res.digits[i + j + 1] += obj1.digits[i] * obj2.digits[j];

	for (int i = length - 1; i > 0; i--)
	{
		res.digits[i - 1] += res.digits[i] / 10;
		res.digits[i] %= 10;
	}
	
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (res.digits[i] == 0)
			count++;
		else
			break;
	}
	
	int* tmp = new int[length - count];
	for (int i = count; i <= length - count; i++)
	{
		tmp[i - count] = res.digits[i];
	}
	delete[] res.digits;

	res.digits = tmp;
	res.size = length - count;
	return res;
}
BigInt::BigInt(int a)
{
	digits = new int[capacity];
	if (a < 0)
	{
		isNegative = true;
		a = abs(a);
	}
	int count = 0;
	while (a)
	{
		count++;
		push(a % 10);
		a /= 10;
	}
	int* tmp = new int[count];
	for (int i = 0; i < count; i++)
	{
		tmp[i] = digits[count - i - 1];
	}
	delete[] digits;
	digits = tmp;
}
BigInt operator-(const BigInt& obj1, const BigInt& obj2)
{
	int size_a = obj1.size - 1;
	int size_b = obj2.size - 1;
	
	
	if (!obj1.isNegative && obj2.isNegative)
		return obj1 + (-obj2);
	if (obj1.isNegative && !obj2.isNegative)
		return -(-obj1 + obj2);
	if (obj1.isNegative && obj2.isNegative)
		return (-obj2) - (-obj1);
	string str = "";
	if (!obj1.isNegative && !obj2.isNegative)
	{
		if (obj2 < obj1)
		{
			BigInt res;
			int* s = new int[obj1.size + 1];
			res.digits = new int[obj1.size + 1];
			for (int i = 0; i < obj1.size + 1; i++)
			{
				s[i] = 0;
				res.digits[i] = 0;
			}
			int min_len = min(size_a, size_b);
			int max_len = max(size_a, size_b);
			for (int i = 0; i <= min_len; i++)
			{
				int tmp = obj1.digits[size_a] - obj2.digits[size_b] - s[size_a + 1];
				if (tmp >= 0)
					res.digits[i] = tmp;
					
				else
				{
					s[size_a] += 1;
					res.digits[i] = tmp + 10;
					
				}
				size_b--;
				size_a--;
			}
			for (int i = min_len + 1; i <= max_len; i++)
			{
				int tmp = obj1.digits[size_a] - s[size_a + 1];
				if (tmp >= 0)
					res.digits[i] = tmp;
					
				else
				{
					s[size_a] += 1;
					res.digits[i] = tmp + 10;
					
				}
				size_b--;
				size_a--;

			}
			delete[] s;
			
			
			int count = 0;
			for (int i = max_len; i >= 0; i--)
			{
				if (res.digits[i] == 0)
					count++;
				else
					break;
			}
			int* tmp = new int[max_len + 1 - count];
			for (int i = 0; i < max_len + 1 - count; i++)
			{
				tmp[i] = res.digits[max_len - count - i];
			}
			
			delete[] res.digits;
			res.digits = tmp;
			res.size = max_len + 1 - count;
			
			return res;
		}
		else
		{
			return -(obj2 - obj1);
		}
	}

}
BigInt BigInt::operator=(const BigInt & obj)
{
	int* tmp = new int[obj.capacity];
	for (int i = 0; i < obj.size; i++)
	{
		tmp[i] = obj.digits[i];
	}
	digits = tmp; 
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
	return *this;
}
BigInt::BigInt(BigInt&& obj)
{
	digits = obj.digits;
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
	obj.digits = nullptr;
}

