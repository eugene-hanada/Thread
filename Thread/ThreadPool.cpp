#include <algorithm>
#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool()
{
	worker_.resize(2);
	for (unsigned int i = 0; i < 2; i++)
	{
		worker_[i].SetIdx(i);
	}
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::Task(std::function<void(void)>&& task)
{
	std::lock_guard<std::mutex> loack(mutex_);
	taskQueue_.emplace_back(std::move(task), [this](unsigned int idx) { EndColl(idx); });
	Check();
}

void ThreadPool::Task(std::function<void(void)>&& task, std::function<void(void)>&& collBack)
{
	std::lock_guard<std::mutex> loack(mutex_);
	taskQueue_.emplace_back(std::move(task), [this, &collBack](unsigned int idx) { collBack(); EndColl(idx); });
	Check();
}





void ThreadPool::Work(int idx, std::stop_token token)
{
}

void ThreadPool::Check(void)
{

	for (unsigned int i = 0; i < 2; i++)
	{
		if (taskQueue_.size() == 0U)
		{
			return;
		}
		if (!worker_[i].HaveTask())
		{
			worker_[i].SetTask(std::move(taskQueue_.begin()->first), std::move(taskQueue_.begin()->second));
			taskQueue_.pop_front();
		}
	}
}

void ThreadPool::EndColl(unsigned int idx)
{
	std::lock_guard<std::mutex> lock(mutex_);
	std::cout << "処理終了" << std::endl;
	if (taskQueue_.size() == 0U)
	{
		return;
	}
	worker_[idx].SetTask(std::move(taskQueue_.begin()->first), std::move(taskQueue_.begin()->second));
	taskQueue_.pop_front();

}

Worker::Worker() :
	idx_{0}
{
	thread_ = std::jthread{ [this](std::stop_token token) { Run(token); } };
}

Worker::Worker(const Worker& w) 
{

}

Worker::~Worker()
{
	std::lock_guard<std::mutex> lock(mutex_);
	thread_.request_stop();
	flag_ = true;
	cd_.notify_all();
	thread_.detach();
}

void Worker::SetTask(std::function<void(void)>&& task, std::function<void(unsigned int)>&& collBack)
{
	task_ = std::move(task);
	collBack_ = std::move(collBack);
	flag_ = true;
	cd_.notify_all();
}

const bool Worker::HaveTask(void)
{
	std::lock_guard<std::mutex> lock(mutex_);
	return flag_;
}

void Worker::SetIdx(unsigned int idx)
{
	idx_ = idx;
}

void Worker::Run(std::stop_token token)
{
	std::cout << "スレッド開始" << std::endl;
	while (!token.stop_requested())
	{
		std::unique_lock<std::mutex> lock(mutex_);
		cd_.wait(lock, [this]() { return flag_; });
		std::cout << "処理開始" << std::endl;
		if (task_ && collBack_)
		{
			task_();
			flag_ = false;
			collBack_(idx_);
		}
	}
	std::cout << "スレッド終了" << std::endl;
}
