#pragma once
#include "Singleton.h"

class Score : public Singleton<Score>
{
	friend class Singleton<Score>;
private:
	Score() : killCount(0), goldEarned(0), timeFlew(0) {}
	~Score() {}
private:
	int killCount;
	int goldEarned;
	float timeFlew;
public:
	void Reset() { killCount = 0; goldEarned = 0; timeFlew = 0; }

	int GetKillCount() { return killCount; }
	int GetEarnedGold() { return goldEarned; }
	float GetTimeFlew() { return timeFlew; }

	void AddKillCount(int count) { killCount += count; }
	void EarnGold(int gold) { goldEarned += gold; }
	void SetTimeFlew(float timeFlew) { this->timeFlew = timeFlew; }
};