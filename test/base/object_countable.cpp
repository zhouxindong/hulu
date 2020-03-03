#include "stdafx.h"
#include "base/object_countable.h"
#include <iostream>

using namespace std;
using namespace hulu;

class C1 {
public:
	C1(int ii, double dd) : i(ii), d(dd) {}
	int i;
	double d;
};

//int main()
//{
//	hulu::Object_countable<C1> c(3, 992.3);
//	std::cout << c.d << '\n';
//	std::cout << c.i << '\n';
//	std::cout << "live: " << c.live() << '\n';
//	
//	hulu::Object_countable<C1> c2(c);
//	std::cout << c2.d << '\n';
//	std::cout << c2.i << '\n';
//	std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//
//	hulu::Object_countable<C1> c3(std::move(c2));
//	std::cout << c3.d << '\n';
//	std::cout << c3.i << '\n';
//	std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//
//	{
//		hulu::Object_countable<C1> c4 = c;
//		std::cout << c4.d << '\n';
//		std::cout << c4.i << '\n';
//		std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//	}
//	std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//
//	hulu::Object_countable<C1>* pc = new hulu::Object_countable<C1>(1, 0.001);
//	std::cout << pc->d << '\n';
//	std::cout << pc->i << '\n';
//	std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//	
//	delete pc;
//	std::cout << "live: " << hulu::Object_countable<C1>::live() << '\n';
//
//
//	system("pause");
//	return 0;
//}