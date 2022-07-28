#include <iostream>
#include <Windows.h>
#include "Thread.h"
#include "LoopThread.h"
#include "AsyncLoad.h"

int main(int argc, char* argv[])
{
	AsyncLoad load;
	load.Load("");
	std::cout << "開始" << std::endl;
	while (!load.IsLoaded())
	{
		// ロード中
	}
	std::cout << "終了" << std::endl;
	return 0;
}