#pragma once
#include "Singleton.h"
struct PowerStat {
	int Might, MaxHealth, Armor, Amount, Cooldown, Area, 
		Velocity, Duration, Speed, Magnet, Luck, Growth;
};

class Power :public Singleton<Power>
{
	friend class Singleton<Power>;
private:
	PowerStat powerStat;
};