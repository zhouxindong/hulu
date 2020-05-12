#include "stdafx.h"
#include "base/singlable.h"
#include <iostream>
#include <cassert>

using namespace std;

class C2 {
public:
	C2(int ii, double dd) : i(ii), d(dd) {}
	int i;
	double d;
};

/*
int main()
{
	//hulu::Singlable<C2> c; // compile error
	//hulu::Singlable<C2> c2; // compile error
	C2& c = hulu::Singlable<C2>::inst_obj(3, 3.14);
	std::cout << c.d << '\n';
	std::cout << c.i << '\n';

	C2& c2 = hulu::Singlable<C2>::inst_obj(9, 9.999); // no change
	std::cout << c2.d << '\n';
	std::cout << c2.i << '\n';

	C2* cp = hulu::Singlable<C2>::inst_ptr(5, 3.2);
	std::cout << cp->d << '\n';
	std::cout << cp->i << '\n';

	assert(&c == &c2);

	system("pause");
	return 0;
}
*/