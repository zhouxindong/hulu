// thread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "thread/spin_lock.h"

#include <thread>
#include <iostream>

using namespace hulu;
using namespace std;

Spin_lock spin;
Spin_lock spin2;
Spin_lock spin3;

void f1_cb()
{
	cout << "f1_cb()\n";
	Sleep(1000);
}

void f(int n)
{
	spin.spin(f1_cb);
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

void f3()
{
	spin.spin();
	cout << "after spin() in f3\n";
}

int main()
{
	thread t1(f, 1); // a thread to spin
	thread t2(f2);   // another thread to spin
	thread t3(f3);

	system("pause");
	spin.release();

	t1.join();
	t2.join();
	t3.join();

	system("pause");
    return 0;
}

