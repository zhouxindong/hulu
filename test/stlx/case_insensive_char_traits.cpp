// stlx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include "stlx/case_insensive_char_traits.h"

int main()
{
	hulu::Case_insensive_string s("AbcDe");

	assert(s == "abcde");
	assert(s == "ABCDE");
	assert(s != "aBcD");
	system("pause");
    return 0;
}

