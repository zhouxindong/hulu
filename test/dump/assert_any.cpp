// dump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "dump/assert_any.h"

int main()
{
	OutputDebugStringA("sofsidfas");
	ASSERT_ANY(true);

	system("pause");
	ASSERT_ANY(false);
	OutputDebugStringA("sofsidfas3234234");
	system("pause");
	return 0;
}

