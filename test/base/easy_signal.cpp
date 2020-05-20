#include "stdafx.h"
#include "base/easy_signal.h"
#include <iostream>

using namespace hulu;

void showme()
{
	std::cout << "showme()\n";
}

class Functor
{
public:
	void operator()() const
	{
		std::cout << "Functor::operator() const\n";
	}
};

class Base
{
public:
	void foo() const
	{
		std::cout << "Base::foo()\n";
	}
};


int main()
{
	Easy_signal<void()> sig;
	sig.connect(showme);
	sig.connect(Functor());
	sig.connect([]() {std::cout << "lambda\n"; });
	sig.connect(&Base::foo, Base());

	Easy_signal<void()> sig2 = sig;
	sig2();

	Easy_signal<void()> sig3;
	sig3 = sig2;
	sig3();

	Easy_signal<void()> sig4 = std::move(sig3);
	sig4();

	Easy_signal<void()> sig5;
	sig5 = std::move(sig4);
	sig5();

	Easy_signal<void()> sig6;
	sig6.connect(sig5);
	sig6();

	return 0;
}
