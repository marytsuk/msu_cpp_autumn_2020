#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
enum class Error
{
	NoError,
	CorruptedArchive
};

class Serializer
{
	stringstream& output;
	static constexpr char Separator = ' ';

	Error process(bool value);
	Error process(uint64_t value);
	template <class T, class... ArgT>
	Error process(T&& t, ArgT&&... args);
public:
	Serializer(stringstream& out);
	template<class T>
	Error save(T& object);
	template<class... ArgsT>
	Error operator()(ArgsT&&... args);
	
};

class Deserializer
{
	stringstream & input;
	
public:
	Deserializer(stringstream&);

	Error process(bool& value);
	Error process(uint64_t& value);
	template <class T, class... ArgT>
	Error process(T&& t, ArgT&&...);
	template <class T>
	Error load(T& object);
	template <class... ArgT>
	Error operator()(ArgT&&... args);
};
struct Data
{
	uint64_t  a;
	bool b;
	uint64_t  c;

	template <class Serializer>
	Error serialize(Serializer& serializer);
};
template <class Serializer>
Error Data::serialize(Serializer& serializer)
{
	return serializer(a, b, c);
	
}
Serializer::Serializer(stringstream& out) : output{ out }
{
}

Error Serializer::process(bool value)
{
	if (value)
	{
		output << "true" << Separator;
		
	}
	else
	{
		output << "false" << Separator;
		
	}
	return Error::NoError;
}

Error Serializer::process(uint64_t value)
{
	output << value << Separator;
	return Error::NoError;
}

template <class T, class... ArgT>
Error Serializer::process(T&& t, ArgT&&... args)
{
	if (process(forward<T>(t)) == Error::NoError)
	{
		return process(forward<ArgT>(args)...);
	}
	
	return Error::NoError;
	
}

template <class... ArgT>
Error Serializer::operator()(ArgT&&... args)
{
	return process(forward<ArgT>(args)...);
}

template <class T>
Error Serializer::save(T& object)
{
	cout << "Serializer works" << endl;
	return object.serialize(*this);
}

Deserializer::Deserializer(stringstream& in) : input{ in }
{
}

Error Deserializer::process(bool& value)
{
	string str;
	input >> str;
	//cout << "str: "<<str << endl;
	if (str == "true")
	{
		value = true;
		
	}
	else if (str == "false")
	{
		value = false;
		
	}
	else
	{
		cout << "invalid_bool_argument" << endl;
		return Error::CorruptedArchive;
	}
	return Error::NoError;
}

Error Deserializer::process(uint64_t& value)
{
	string str;
	input >> str;
	//cout << "str: "<<str << endl;
	try
	{
		value = stoull(str, nullptr, 10);
	}
	catch (...)
	{
		cout << "invalid_argument" << endl;
		return Error::CorruptedArchive;
	}
	//value = atoi(str.c_str());
	return Error::NoError;
}

template <class T, class... ArgT>
Error Deserializer::process(T&& t, ArgT&&... args)
{
	if (process(forward<T>(t)) == Error::NoError)
	{
		return process(forward<ArgT>(args)...);
	}

	return Error::CorruptedArchive;
}

template <class... ArgT>
Error Deserializer::operator()(ArgT&&... args)
{
	if (process(forward<ArgT>(args)...) == Error::NoError)
	{
		return Error::NoError;
	}
	
	return Error::CorruptedArchive;
	
}

template <class T>
Error Deserializer::load(T& object)
{
	cout << "Deserializer works" << endl;
	return object.serialize(*this);
	
}