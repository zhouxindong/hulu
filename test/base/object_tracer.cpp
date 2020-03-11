#include "stdafx.h"
#include "base/object_tracer.h"
#include <iostream>

using namespace std;
using namespace hulu;

class Y : public Inst_trace_base
{
public:
	Y() {
		cout << "Y::Y()\n";
	}

	Y(double d) : d_(d) {
		cout << "Y::Y(double)\n";
	}

	~Y()
	{
		cout << "Y::~Y()\n";
	}

	void show()
	{
		cout << d_ << '\n';
	}

private:
	double d_;
	int i_[13];
	char ch_;
};

int main()
{
	Y* p = new Y(33.9);
	p->show();

	Y* p2 = new Y(0.2323);
	p2->show();

	delete p;
	//delete p2;

	Inst_trace_base* pa = new Y[12]; // base point
	Y* pb = new Y[100];
	//delete[] pa;

	Y::print(cout);

	system("pause");

	Y::delete_all<Y>();

	system("pause");
	return 0;
}