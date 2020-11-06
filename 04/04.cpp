
#include <iostream>
#include "BigInt.h"
#include <string>
#include <assert.h>
using namespace std;
int main()
{
	
	/*BigInt ob1("-12");
	string str2 = "-6";
	BigInt ob2(str2);
	
	BigInt b = -1000004;
	BigInt c = ob1 - ob2;
	bool f = ob1 >= ob2;
	BigInt d;
	d = std::move(b);
	cout << d;*/

	BigInt ob1("123456789123456789");
	BigInt test1("123456789123456789");
	BigInt test2("123456789123456785");
	cout << "(123456789123456789) test1 = " << ob1 << endl;
	cout << endl;

	bool flag = (test1 == ob1);
	assert(flag == true);

	flag = (ob1 != test2);
	assert(flag == true);

	flag = (test1 > test2);
	assert(flag == true);
	flag = (test1 < test2);
	assert(flag == false);

	flag = (test1 <= test2);
	assert(flag == false);
	flag = (test1 >= test2);
	assert(flag == true);

	flag = (ob1 <= test1);
	assert(flag == true);
	flag = (ob1 >= test1);
	assert(flag == true);

	
	BigInt ob2("6789");
	BigInt ob3("123456");
	BigInt test3 = ob2 + ob3;
	cout << "(6789 + 123456 = 130245) test3 = " << test3 << endl;
	assert(test3.ReturnString() == "130245");
	
	BigInt test4 = ob2 - ob3;
	cout << "(6789 - 123456 = -116667) test4 = " << test4 << endl;
	assert(test4.ReturnString() == "-116667");

	BigInt test5 = ob3 - ob2;
	cout << "(123456 - 6789 = 116667) test5 = " << test5 << endl;
	assert(test5.ReturnString() == "116667");

	BigInt test6 = ob3 * ob2;
	cout << "(123456 * 6789 = 838142784) test6 = " << test6 << endl;
	assert(test6.ReturnString() == "838142784");

	cout << endl;
	
	BigInt test7 = -ob2 + ob3;
	cout << "(-6789 + 123456 = 116667) test7 = " << test7 << endl;
	assert(test7.ReturnString() == "116667");

	BigInt test8 = -ob2 - ob3;
	cout << "(-6789 - 123456 = -130245) test8 = " << test8 << endl;
	assert(test8.ReturnString() == "-130245");

	BigInt test9 = ob3 - (-ob2);
	cout << "(123456 - (-6789) = 130245) test9 = " << test9 << endl;
	assert(test9.ReturnString() == "130245");

	BigInt test10 = ob3 * (-ob2);
	cout << "(123456 * (-6789) = -838142784) test10 = " << test10 << endl;
	assert(test10.ReturnString() == "-838142784");

	cout << endl;
	

	BigInt test11 = ob2 + (-ob3);
	cout << "(-6789 + (-123456) = -130245) test11 = " << test11 << endl;
	assert(test11.ReturnString() == "-130245");

	BigInt test12 = ob2 -(-ob3);
	cout << "(-6789 - (-123456) = 116667) test12 = " << test12 << endl;
	assert(test12.ReturnString() == "116667");

	BigInt test13 = -ob3 - ob2;
	cout << "(-123456 - (-6789) = -116667) test13 = " << test13 << endl;
	assert(test13.ReturnString() == "-116667");

	BigInt test14 = (-ob3) * ob2;
	cout << "(-123456 * (-6789) = 838142784) test14 = " << test14 << endl;
	assert(test14.ReturnString() == "838142784");
	
	BigInt ob4;
	ob4 = std::move(ob2);
	cout << "(-6789) test15 = " << ob4 << endl;
	assert(ob4.ReturnString() == "-6789");

	BigInt ob5("999999999999999999999999");
	BigInt ob6("999999999999999999999999");
	BigInt str = ob5 * ob6;
	cout << str;
	return 0;

}

