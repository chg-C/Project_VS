#include "Include.h"
#include "Time.h"

Time::Time()
    : startTime(), frequency(), endTime(), frameTime(0)
{
}

void Time::InitTime()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime);
}

void Time::UpdateTime(double speed)
{
    QueryPerformanceCounter(&endTime);
    frameTime = (static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart) * speed;
    startTime = endTime;
}
