#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include <typeinfo>
#include <sstream>
using namespace std;

stringstream ss;
int c = 0;
string separator = " ";
class MyData
{
private:
	int a, b;

public:
	MyData(int a1, int b1) : a{ a1 }, b{ b1 }
	{

	}
	friend ostream& operator<<(ostream& out, const MyData& d)
	{
		out << d.a << "+" << d.b;
		return out;
	}
};

struct callback
{
	template<typename T>
	void operator()(int index, T&& t)
	{             
		c++;
		ss << t << separator;
	}
};
namespace _detail_
{
	template<int index, typename Callback, typename... Args>
	struct iterate_tuple
	{
		static void next(tuple<Args...>& t, Callback callback)
		{
			iterate_tuple<index - 1, Callback, Args...>::next(t, callback);
			callback(index, get<index>(t));
		}
	};
	template<typename Callback, typename... Args>
	struct iterate_tuple<0, Callback, Args...>
	{
		static void next(tuple<Args...>& t, Callback callback)
		{
			callback(0, get<0>(t));
		}
	};
	template<typename Callback, typename... Args>
	struct iterate_tuple<-1, Callback, Args...>
	{
		static void next(tuple<Args...>& t, Callback callback)
		{
		
		}
	};
}
template<typename Callback, typename... Args>
void for_each(tuple<Args...>& t, Callback callback)
{
	int const t_size = tuple_size<tuple<Args...>>::value;
	_detail_::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}


template <class... ArgT>
string format(string str, ArgT&&... args)
{
	auto tuple_params = make_tuple(forward<ArgT>(args)...);
	
	string result;
	ss.clear();
	c = 0;
	
	for_each(tuple_params, callback());

	vector<string> params;
	for (int i = 0; i < c; i++)
	{
		string tmp;
		ss >> tmp;
		params.push_back(tmp);
	}

	/*for (int i = 0; i < c; i++)
	{
		
		cout << params[i] << endl;
	}*/
	
	for (int i = 0; i < str.length(); i++)
	{
		while (str[i] != '{')
		{
			result.push_back(str[i]);
			i++;
			if (i == str.length())
				break;
		}
		
		if (i == str.length())
			break;

		string tmp;
		i++;

		while (str[i] != '}')
		{
			
			if (i < str.length())
				tmp.push_back(str[i]);
			else
				throw runtime_error("Invalid bracket sequence!\n");
			i++;
		}
		for (int i = 0; i < tmp.length(); i++)
		{
			if (!isdigit(tmp[i]))
				throw runtime_error("Invalid format of parameter!\n");
		}
		
		if (strtoul(tmp.c_str(), NULL, 10) < params.size())
		{
			//cout << params.size() << endl;
			//cout << strtoul(tmp.c_str(), NULL, 10) << endl;
			result = result + params[strtoul(tmp.c_str(), NULL, 10)];
		}
		else
			throw runtime_error("Invalid number of arguments!\n");
	}
	return result;
}