
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
vector<string> myOutStr;
vector<int> myOutNum;
class TokenParser
{
	string myString = "";
	DefaultType start = nullptr;
	DefaultType end = nullptr;
	NumType number = nullptr;
	StrType str = nullptr;
public:
	TokenParser(const string& s);
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
	int i = 0;
	do
	{
		bool flag = false;
		c = myString[i];
		if (state == OUT && isdigit(c))
		{
			state = IN1;
			token.push_back(c);
			flag = true;
		}
		if (state == OUT && !(isdigit(c) || isspace(c)))
		{
			state = IN2;
			token.push_back(c);
			flag = true;
		}
		else if (state == IN1 && isspace(c))
		{
			state = OUT;
			number(atoi(token.c_str()));
			token = "";
			flag = true;
		}
		else if ((state == IN2 || state == IN3) && isspace(c))
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
		else if (state == IN1 && !(isdigit(c) || isspace(c)))
		{
			state = IN3;
			token.push_back(c);
			flag = true;
		}
		else if (!flag)
		{
			token.push_back(c);
		}
		i++;
	} while (i != myString.length());

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
TokenParser::TokenParser(const string& s)
{
	myString = s;
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
	myOutNum.push_back(num);
}
void myString(const string& str)
{
	cout << str << " this is word!" << endl;
	myOutStr.push_back(str);
}
int main()
{
	TokenParser test("cat 1234 34dog3 cat34 6879 ");
	test.SetStartCallback(myStart);
	test.SetEndCallback(myEnd);
	test.SetDigitTokenCallback(myDigit);
	test.SetStrTokenCallback(myString);
	test.Parse();

	vector<string> resStr;
	vector<int> resNum;
	resStr.push_back("cat");
	resNum.push_back(1234);
	resStr.push_back("34dog3");
	resStr.push_back("cat34");
	resNum.push_back(6879);
	
	for (int i = 0; i < myOutStr.size(); i++)
	{
		if (myOutStr[i] == resStr[i])
			cout << "SUCCESS!" << endl;
		else
			cout << "FAIL!" << endl;
	}
	for (int i = 0; i < myOutNum.size(); i++)
	{
		if (myOutNum[i] == resNum[i])
			cout << "SUCCESS!" << endl;
		else
			cout << "FAIL!" << endl;
	}
	return 0;
}

