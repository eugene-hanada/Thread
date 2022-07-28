#include "Thread.h"


Thread::Thread()
{
	runFlag_.store(false);
	th_ = std::jthread{ &Thread::Run,this };
}

Thread::~Thread()
{
	th_.detach();
}

void Thread::Begin()
{
	if (!runFlag_.load())
	{
		runFlag_.store(true);
	}
}

void Thread::Set(const std::function<void(void)>& task)
{
	if (!runFlag_.load())
	{
		task_= task;
	}
	
}

void Thread::Wait(void) const noexcept
{
	while (runFlag_.load())
	{
		std::this_thread::yield();
	}
}


void Thread::Run()
{
	while (true)
	{
		if (runFlag_.load())
		{
			task_();
			runFlag_.store(false);
		}
		std::this_thread::yield();
	}
}
