#include "stdafx.h"
#include "base/easy_signal.h"
#include <iostream>

using namespace hulu;

void showme(int)
{
	std::cout << "showme()\n";
}

class Functor
{
public:
	void operator()(int) const
	{
		std::cout << "Functor::operator() const\n";
	}
};

class Base
{
public:
	void foo(int) const
	{
		std::cout << "Base::foo()\n";
	}
};

class Bar
{
public:
	std::string operator()(double) const
	{
		std::cout << "Bar::operator()(double)\n";
		return "operator()";
	}

	void foo(int) const
	{
		std::cout << "Bar::foo -> double:std::string\n";
	}

	std::string foo2(double) const
	{
		std::cout << "Bar::foo2\n";
		return "foo2";
	}
};

int main()
{
	Easy_signal<void(int)> sig;
	sig.connect(showme);
	sig.connect(Functor());
	sig.connect([](int) {std::cout << "lambda\n"; });
	sig.connect(&Base::foo, Base());
	sig.connect(&Bar::foo, Bar());
	sig(3);

	Easy_signal<std::string(double)> sigg;
	sigg.connect(&Bar::foo2, Bar());
	sigg(23.232);

	system("pause");

	Easy_signal<void(int)> sig2 = sig;
	sig2(0);

	Easy_signal<void(int)> sig3;
	sig3 = sig2;
	sig3(0);

	Easy_signal<void(int)> sig4 = std::move(sig3);
	sig4(1);

	Easy_signal<void(int)> sig5;
	sig5 = std::move(sig4);
	sig5(2);

	Easy_signal<void(int)> sig6;
	sig6.connect(sig5);
	sig6(3);

	return 0;
}
