// base.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "base/noncopyable.h"

class C1 {
public:
	C1(int i1 = 0, double d1 = 0) : i(i1), d(d1) {}
	int i;
	double d;

	void show1() const {
		std::cout << "C1::show1()\n";
	}
};

class C2 : public C1 {
public:
	C2(int i1 = 0, double d1 = 0, std::string s1 = "") :
		C1(i1, d1), s(std::move(s1)) {}
	C1 c1;
	std::string s;

	void show2() const {
		std::cout << "C2::show2()\n";
	}
};

class C3
{
public:
	C3(float f1) : f(f1) {}
	float f;

	void show3() const {
		std::cout << "C3::show3()\n";
	}
};

/*
int main()
{
	//hulu::Non_copyable<C2> c;
	hulu::Non_copyable<C2> c(3, 5.3, "hello");
	std::cout << c.i << "\n";
	std::cout << c.d << "\n";
	std::cout << c.s << "\n";
	c.show1();
	c.show2();

	//hulu::Non_copyable<C2> c2(c); // compile error
	hulu::Non_copyable<C2> c2(std::move(c)); // ok
	std::cout << c2.i << "\n";
	std::cout << c2.d << "\n";
	std::cout << c2.s << "\n";
	c2.show2();

	hulu::Non_copyable<C2> c3(99);
	std::cout << c3.i << "\n";
	std::cout << c3.d << "\n";
	std::cout << c3.s << "\n";
	c3.show1();

	hulu::Non_copyable<C3> cc(3.1413f);
	std::cout << cc.f << '\n';

	//hulu::Non_copyable<C3> cc2(cc); // compile error
	hulu::Non_copyable<C3> cc2(std::move(cc));
	std::cout << cc2.f << '\n';
	cc.show3();

	system("pause");
    return 0;
}
*/
