#include "stdafx.h"
#include <iostream>
#include "base/presuffixable.h"

void prefix()
{
	std::cout << "prefix()\n";
}

void suffix()
{
	std::cout << "suffix()\n";
}

class X {
public:
	X() {
		std::cout << "make an X\n";
	}

	~X() {
		std::cout << "destroy an X\n";
	}

	int f() const
	{
		std::cout << "X::f()\n";
		return 1;
	}

	void g() const
	{
		std::cout << "X::g()\n";
	}
};

class Y
{
public:
	Y() {
		std::cout << "make a Y\n";
	}

	~Y() {
		std::cout << "destroy a Y\n";
	}

	void h() const
	{
		std::cout << "Y::h()\n";
	}
};

struct Pref
{
	void operator()() const
	{
		std::cout << "Pref\n";
	}
};

struct Suf
{
	void operator()() const
	{
		std::cout << "Suf\n";
	}
};
//int main()
//{
//	hulu::Pre_suffixable<X, void(*)(), void(*)()> xx(new X, prefix, suffix);
//	hulu::Pre_suffixable<Y, void(*)(), void(*)()> yy(new Y, prefix, suffix);
//	hulu::Pre_suffixable<X, void(*)(), void(*)()> x2 = xx;
//
//	X x;
//	hulu::Pre_suffixable<X, Pref, Suf> x3(x, Pref(), Suf());
//
//	if (xx->f()) std::cout << "done\n";
//	xx->g();
//	x2->g();
//	xx = x2;
//	x2->g();
//	x3->g();
//	yy->h();
//
//	system("pause");
//	return 0;
//}