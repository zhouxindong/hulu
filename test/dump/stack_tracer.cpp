#include "stdafx.h"
#include "dump/stack_tracer.h"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace hulu;

class X {
public:
	void showme() {
		cout << Stack_tracer::stack_trace();
	}
};

//int main()
//{
//	cout << "-------------stack_trace()----------------" << endl;
//	cout << Stack_tracer::stack_trace("prefix", "surfix") << endl;
//	cout << "-------------stack_trace2()---------------" << endl;;
//	cout << Stack_tracer::stack_trace2("prefix2", "surfix2") << endl;
//
//	cout << "\n\n";
//	X().showme();
//	cout << "\n";
//
//	system("pause");
//	return 0;
//}