#pragma once
#include <atomic>
#include <thread>
#include <string>

class AsyncLoad
{
public:
	void Load(const std::string& fname);
	void MyLoad(const std::string& fname);
	bool IsLoaded(void);
private:
	std::jthread th_;
	std::atomic_bool result_;
};

