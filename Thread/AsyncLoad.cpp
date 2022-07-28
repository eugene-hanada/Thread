#include <Windows.h>
#include <iostream>
#include "AsyncLoad.h"

void AsyncLoad::Load(const std::string& fname)
{
	result_.store(false);
	th_ = std::jthread{ &AsyncLoad::MyLoad,this,fname};
}

void AsyncLoad::MyLoad(const std::string& fname)
{
	Sleep(100);
	std::cout << "���[�h����" << std::endl;
	result_.store(true);
}


bool AsyncLoad::IsLoaded(void)
{
	return result_.load();
}
