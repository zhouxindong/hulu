// thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "thread/spin_lock.h"

#include <thread>
#include <iostream>

using namespace hulu;
using namespace std;

Spin_lock spin;

void f(int n)
{
	spin.spin();
	cout << "after spin() in f(int n)\n";
}

void f2_cb(int c)
{
	static int count = c;
	cout << ++count << '\n';
	Sleep(1000);
}

void f2()
{
	spin.spin(f2_cb, 0);
	cout << "after spin() in f2()\n";
}

void g(int n)
{
	cout << "g(int n) is going to start.\n";
	spin.release();
	cout << "after release() in g(int n)\n";
}

int main()
{
	thread t1(f, 1); // a thread to spin
	system("pause");
	thread t3(f2);   // another thread to spin
	system("pause");
	//thread t2(g, 2); // a thread to release spin
	//system("pause");
	spin.release_all();

	t1.join();
	//t2.join();
	t3.join();
	system("pause");

    return 0;
}

