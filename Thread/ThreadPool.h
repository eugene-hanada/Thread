#pragma once
#include <thread>
#include <condition_variable>
#include <deque>
#include <functional>
#include <atomic>
#include <vector>
#include <tuple>

class Worker
{
public:
	Worker();
	Worker(const Worker& w);
	~Worker();
	void SetTask(std::function<void(void)>&& task, std::function<void(unsigned int)>&& collBack);
	const bool HaveTask(void);
	void SetIdx(unsigned int idx);
private:
	void Run(std::stop_token token);

	unsigned int idx_;
	std::jthread thread_;
	std::mutex mutex_;

	std::function<void(void)> task_;
	std::function<void(unsigned int)> collBack_;
	std::condition_variable cd_;
	bool flag_{ false };

};

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void Task(std::function<void(void)>&& task);
	void Task(std::function<void(void)>&& task, std::function<void(void)>&& collBack);
private:
	void Work(int idx, std::stop_token token);
	void Check(void);
	void EndColl(unsigned int idx);
	std::mutex mutex_;
	
	std::vector<Worker> worker_;
	using TaskPair = std::pair<std::function<void(void)>, std::function<void(unsigned int)>>;
	std::deque<TaskPair> taskQueue_;
};

