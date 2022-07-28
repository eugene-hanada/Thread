#pragma once
#include <thread>
#include <atomic>

class LoopThread
{
public:
	LoopThread();
	virtual ~LoopThread();
	void Stop(void) noexcept;
	void Start(void) noexcept;
protected:
	void Loop(void);
	virtual void Run(void);
private:
	std::jthread th_;
	std::atomic_bool endflag_;
	std::atomic_bool runflag_;
};

