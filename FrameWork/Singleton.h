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
	//���� ����
	Singleton(const Singleton&) {}
	Singleton& operator=(const Singleton&) {}
protected:
	Singleton() {

	}
	virtual ~Singleton() {

	}
};