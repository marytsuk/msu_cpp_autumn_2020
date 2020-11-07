#include "BigInt.h"
#include <string.h>
#include <algorithm>
using namespace std;
string BigInt::ReturnString() const
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

	int count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '0')
			count++;
		else
			break;
	}
	
	if (count  == str.length())
	{
		push(0);
		return;
	}
		

	for (int i = count; i < str.length(); i++)
	{
		push(str[i] - '0');
	}
	
	
}
BigInt::BigInt(const BigInt& obj)
{
	int* tmp = new int[obj.capacity];
	for (int i = 0; i < obj.size; i++)
	{
		tmp[i] = obj.digits[i];
	}
	if (digits != nullptr)
		delete[] digits;
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
		//BigInt res;
		//res.digits = new int[length + 1];
		int carry = 0;
		//res.size = length + 1;
		//res.capacity = length + 1;
		//res.isNegative = false;
		for (int i = length; i >= 0; i--)
		{
			if (size_a < 0)
			{
				int sum = obj2.digits[size_b];
				sum += carry;
				//res.digits[i] = sum % 10;
				str.push_back((char)(sum % 10 + '0'));
				
				carry = sum / 10;
				size_b--;
				continue;
			}
			if (size_b < 0)
			{
				int sum = obj1.digits[size_a];
				sum += carry;
				
				//res.digits[i] = sum % 10;
				str.push_back((char)(sum % 10 + '0'));
				carry = sum / 10;
				size_a--;
				continue;
			}
			
			int sum = obj1.digits[size_a] + obj2.digits[size_b];
			sum += carry;
			//res.digits[i] = sum % 10;
			str.push_back((char)(sum % 10 + '0'));
				
			carry = sum / 10;
			size_a--;
			size_b--;
		}
		
		if (carry)
		{
			
			str.push_back((char)(carry + '0'));

		}
		
		reverse(str.begin(), str.end());
		return BigInt(str);
		//return res;
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
	bool is_neg;

	int* tmp1 = new int[size_a];
	int* tmp2 = new int[size_b];
	int* res = new int[length];
	for (int i = 0; i < size_a; i++)
		tmp1[i] = obj1.digits[size_a - i - 1];
	for (int i = 0; i < size_b; i++)
		tmp2[i] = obj2.digits[size_b - i - 1];
	for (int i = 0; i < length; i++)
		res[i] = 0;
	
	for (int i = 0; i < size_a; i++)
		for (int j = 0, carry = 0; j < size_b || carry; j++)
		{
			int tmp = res[i + j] + tmp1[i] * (j < size_b ? tmp2[j] : 0) + carry;
			res[i + j] = tmp % 10;
			carry = tmp / 10;
		}

		
	if (!obj1.isNegative && !obj2.isNegative || obj1.isNegative && obj2.isNegative)
		is_neg = false;
	else
		is_neg = true;

	string str ="";
	for (int i = 0; i < length; i++)
	{
		str.push_back((char)(res[i] + '0'));
	}
	delete[] res;
	delete[] tmp1;
	delete[] tmp2;
	reverse(str.begin(), str.end());
	string tmpstr="";
	if (is_neg)
		tmpstr.push_back('-');
	int i = 0;
	while (str[i] == '0')
		i++;
	for (int j = i; j < str.size(); j++)
		tmpstr.push_back(str[j]);
	if (tmpstr.size() == 0)
		tmpstr.push_back('0');
	return BigInt(tmpstr);
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
	if (a == 0)
	{
		push(0);
	}
	else
	{
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
			//BigInt res;
			int* s = new int[obj1.size + 1];
			//res.digits = new int[obj1.size + 1];
			for (int i = 0; i < obj1.size + 1; i++)
			{
				s[i] = 0;
				//res.digits[i] = 0;
			}
			int min_len = min(size_a, size_b);
			int max_len = max(size_a, size_b);
			for (int i = 0; i <= min_len; i++)
			{
				int tmp = obj1.digits[size_a] - obj2.digits[size_b] - s[size_a + 1];
				if (tmp >= 0)
					//res.digits[i] = tmp;
					str.push_back((char)(tmp + '0'));
					
				else
				{
					s[size_a] += 1;
					//res.digits[i] = tmp + 10;
					str.push_back((char)(tmp + 10 + '0'));
					
				}
				size_b--;
				size_a--;
			}
			for (int i = min_len + 1; i <= max_len; i++)
			{
				int tmp = obj1.digits[size_a] - s[size_a + 1];
				if (tmp >= 0)
					//res.digits[i] = tmp;
					str.push_back((char)(tmp + '0'));
					
				else
				{
					s[size_a] += 1;
					//res.digits[i] = tmp + 10;
					str.push_back((char)(tmp + 10 + '0'));
					
				}
				size_b--;
				size_a--;

			}
			delete[] s;
			
			reverse(str.begin(), str.end());
			string tmpstr = "";
			int i = 0;
			while (str[i] == '0')
				i++;
			for (int j = i; j < str.size(); j++)
				tmpstr.push_back(str[j]);
			
			if (tmpstr.size() == 0)
				tmpstr.push_back('0');
			return BigInt(tmpstr);
		}
		else
		{
			return -(obj2 - obj1);
		}
	}

}
BigInt& BigInt::operator=(const BigInt& obj)
{
	int* tmp = new int[obj.capacity];
	for (int i = 0; i < obj.size; i++)
	{
		tmp[i] = obj.digits[i];
	}
	if (digits != nullptr)
		delete[] digits;
	digits = tmp; 
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
	return *this;
}
BigInt::BigInt(BigInt&& obj)
{
	if (digits != nullptr)
		delete[] digits;
	digits = obj.digits;
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
	obj.digits = nullptr;
}
BigInt& BigInt::operator=(BigInt&& obj)
{
	if (&obj == this)
		return *this;
	if (digits != nullptr)
		delete[] digits;
	digits = obj.digits;
	size = obj.size;
	capacity = obj.capacity;
	isNegative = obj.isNegative;
	obj.digits = nullptr;
	return *this;
}
