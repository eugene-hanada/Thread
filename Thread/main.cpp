#include <iostream>
#include <Windows.h>
#include "Thread.h"
#include "LoopThread.h"
#include "AsyncLoad.h"
#include "ThreadPool.h"

void Value(int num)
{
	std::cout << num << std::endl;
}

int main(int argc, char* argv[])
{
	{	
		ThreadPool tp;
		std::cout << "ŠJŽn" << std::endl;
		tp.Task([&]() {
			std::cout << "A" << std::endl;
			});
		tp.Task([&]() {
			std::cout << "B" << std::endl;});
		tp.Task([&]() {Value(0); });
		tp.Task([&]() {Value(1); });
		tp.Task([&]() {Value(2); });
		tp.Task([&]() {Value(3); });
		tp.Task([&]() {Value(4); });
		tp.Task([&]() {Value(5); });
		tp.Task([&]() {Value(6); });
		tp.Task([&]() {Value(7); });
		tp.Task([&]() {Value(8); });
		tp.Task([&]() {Value(9); });
		tp.Task([&]() {Value(10); });
		tp.Task([&]() {Value(11); });
		Sleep(5000);
		std::cout << "I—¹" << std::endl;
	}
	return 0;
}