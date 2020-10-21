
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <functional>
using namespace std;

using DefaultType = function<void()>;
using NumType = function<void(int)>;
using StrType = function<void(const string&)>;
char c;
ifstream input("input.txt", ios_base::in);
ofstream output("output.txt",  ios_base::trunc);
void gc()
{
	c = input.get();
}
class TokenParser
{
	DefaultType start = nullptr;
	DefaultType end = nullptr;
	NumType number = nullptr;
	StrType str = nullptr;
public:
	TokenParser();
	void SetStartCallback(DefaultType foo);
	void SetEndCallback(DefaultType foo);
	void SetDigitTokenCallback(NumType foo);
	void SetStrTokenCallback(StrType foo);
	void Parse();

};
void TokenParser::Parse()
{
	start();
	enum set { OUT, IN1, IN2, IN3} state = OUT;

	string token = "";

	do
	{
		bool flag = false;
		gc();
		if (state == OUT && isdigit(c))
		{
			state = IN1;
			token.push_back(c);
			flag = true;
		}
		if (state == OUT && !(isdigit(c) || ((c == ' ') || (c == '\t') || (c == '\n'))))
		{
			state = IN2;
			token.push_back(c);
			flag = true;
		}
		else if (state == IN1 && ((c == ' ') || (c == '\t') || (c == '\n')))
		{
			state = OUT;
			number(atoi(token.c_str()));
			token = "";
			flag = true;
		}
		else if ((state == IN2 || state == IN3) && ((c == ' ') || (c == '\t') || (c == '\n')))
		{
			state = OUT;
			str(token);
			token = "";
			flag = true;
		}
		
		else if (state == IN2 && isdigit(c))
		{
			state = IN3;
			token.push_back(c);
			flag = true;
		}
		else if (state == IN1 && !(isdigit(c) || ((c == ' ') || (c == '\t') || (c == '\n'))))
		{
			state = IN3;
			token.push_back(c);
			flag = true;
		}
		else if (!flag)
		{
			token.push_back(c);
		}
		
	} while (c != EOF);

	end();
}
void TokenParser::SetDigitTokenCallback(NumType foo)
{
	number = foo;
}
void TokenParser::SetStrTokenCallback(StrType foo)
{
	str = foo;
}
void TokenParser::SetStartCallback(DefaultType foo)
{
	start = foo;
}
void TokenParser::SetEndCallback(DefaultType foo)
{
	end = foo;
}
TokenParser::TokenParser()
{

}
void myStart()
{
	cout << "start!" << endl;
}
void myEnd()
{
	cout << "end!" << endl;
}
void myDigit(int num)
{
	cout << num << " this is number!" << endl;
	output << num << endl;
}
void myString(const string& str)
{
	cout << str << " this is word!" << endl;
	output << str << endl;
}
int main()
{
	ifstream result("res.txt", ios_base::in);
	
	TokenParser test;
	test.SetStartCallback(myStart);
	test.SetEndCallback(myEnd);
	test.SetDigitTokenCallback(myDigit);
	test.SetStrTokenCallback(myString);
	test.Parse();

	output.close();

	ifstream output("output.txt", ios_base::in);
	vector<string> myOut;
	vector<string> res;
	string tmp;
	while (result)
	{
		std::getline(result, tmp);
		res.push_back(tmp);
	}
	while (output)
	{
		std::getline(output, tmp);
		myOut.push_back(tmp);
	}
	for (int i = 0; i < myOut.size() - 1; i++)
	{
		if (myOut[i] == res[i])
			cout << "SUCCESS!" << endl;
		else
			cout << "FAIL!" << endl;
	}
	
	return 0;
}

