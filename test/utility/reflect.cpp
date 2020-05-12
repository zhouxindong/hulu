// utility.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utility/reflect.h"
#include <iostream>
#include <string>
#include <map>

using namespace hulu;
using namespace std;

class X {
public:
	double d;
	int i;
	string s;

public:
	X(double dd, int ii, string ss) : d(dd), i(ii), s(ss) {}
};

class A {
public:
	void show()
	{
		cout << "A::show()\n";
	}
};

A* createA() {
	return new A();
}


int main()
{
	//Reflect_base<X>* reflect = new Reflect_base<X>();
	//auto p = reflect->create(3.143, 99, "adfdsadf");
	//cout << p->d << '\n';
	//cout << p->i << '\n';
	//cout << p->s << '\n';


	system("pause");
    return 0;
}

