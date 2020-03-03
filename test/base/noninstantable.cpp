#include "stdafx.h"

#include <string>
#include <iostream>

#include "base/noninstantable.h"

class C1 {
public:
	C1(int i1 = 0, double d1 = 0) : i(i1), d(d1) {}
	int i;
	double d;
};

class C2 : public C1 {
public:
	C2(int i1 = 0, double d1 = 0, std::string s1 = "") :
		C1(i1, d1), s(std::move(s1)) {}
	C1 c1;
	std::string s;
};

class C3
{
public:
	C3(float f1) : f(f1) {}
	float f;
};


//int main()
//{
//	//hulu::Non_instantable<C1> c;	// compile error
//	//hulu::Non_instantable<C1> c(2);	// compile error
//	//hulu::Non_instantable<C1> c(3, 9.232);	// compile error
//
//	system("pause");
//	return 0;
//}