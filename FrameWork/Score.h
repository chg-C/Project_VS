#pragma once
#include "Singleton.h"

class Score : public Singleton<Score>
{
	friend class Singleton<Score>;
private:
	Score() : killCount(0), goldEarned(0) {}
	~Score() {}
private:
	int killCount;
	int goldEarned;
public:
	void Reset() { killCount = 0; goldEarned = 0; }

	int GetKillCount() { return killCount; }
	int GetEarnedGold() { return goldEarned; }

	void AddKillCount(int count) { killCount += count; }
	void EarnGold(int gold) { goldEarned += gold; }
};