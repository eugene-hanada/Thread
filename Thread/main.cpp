#include <iostream>
#include <Windows.h>
#include "Thread.h"
#include "LoopThread.h"
#include "AsyncLoad.h"

int main(int argc, char* argv[])
{
	AsyncLoad load;
	load.Load("");
	std::cout << "�J�n" << std::endl;
	while (!load.IsLoaded())
	{
		// ���[�h��
	}
	std::cout << "�I��" << std::endl;
	return 0;
}