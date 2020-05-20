#include "stdafx.h"
#include "base/pipe_range.h"
#include <iostream>
#include <vector>

double double_it(int i)
{
	return i + 4.92;
}

bool greater_seven(double d)
{
	return d > 7.0;
}

double sum(double x, double y)
{
	return (x + y);
}

/*
int main()
{
	std::vector<int> v{ 1,2,3,4,5,6 };
	auto res = v | std::function<double(int)>(double_it) | std::function<bool(double)>(greater_seven) | std::function<double(double, double)>(sum);

	//auto res = v | std::function<int(int, int)>(sum);

	//for (auto e : v2)
	//{
	//	std::cout << e << '\n';
	//}

	std::cout << res << '\n';
	return 0;
}
//*/