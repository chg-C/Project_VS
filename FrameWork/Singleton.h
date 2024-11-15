#pragma once
#include <mutex>

template <typename T>
class Singleton {
public:
	static T& GetInstance()
	{
		static T instance;

		return instance;
	}
private:
	//복사 방지
	Singleton(const Singleton&) {}
	Singleton& operator=(const Singleton&) {}
protected:
	Singleton() {

	}
	virtual ~Singleton() {

	}
};