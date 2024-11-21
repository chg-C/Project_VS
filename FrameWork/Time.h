#pragma once

class Time : public Singleton<Time>
{
	friend class Singleton<Time>;
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime, endTime;
	double frameTime;
public:
	Time();
public:
	void InitTime();
	void UpdateTime(double speed = 1);
	double GetTime() { return frameTime; }
};

#define TIME Singleton<Time>::GetInstance().GetTime()

