#include <iostream>
#include <functional>
#include "LoopThread.h"

LoopThread::LoopThread()
{
	runflag_.store(false);
	endflag_.store(true);
	th_ = std::jthread{ &LoopThread::Loop, this };
}

LoopThread::~LoopThread()
{
	endflag_.store(false);
	th_.detach();
}


void LoopThread::Stop(void) noexcept
{
	runflag_.store(false);
}

void LoopThread::Start(void) noexcept
{
	runflag_.store(true);
}

void LoopThread::Loop(void)
{
	while (endflag_)
	{
		if (runflag_.load())
		{
			Run();
		}
		else
		{
			std::this_thread::yield();
		}
	}
}


void LoopThread::Run(void)
{
	std::cout << "run" << std::endl;
}
