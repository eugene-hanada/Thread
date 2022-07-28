#pragma once
#include <thread>
#include <functional>
#include <atomic>

class Thread
{
public:
	Thread();
	~Thread();
	void Begin();
	void Set(const std::function<void(void)>& task);
	void Wait(void) const noexcept;
private:
	void Run();
	std::jthread th_;
	std::atomic_bool runFlag_;
	std::function<void(void)> task_;
};

