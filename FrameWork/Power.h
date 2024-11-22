#pragma once
class Power
{
	int curLevel;
	int maxLevel;
public:
	Power(int _maxLevel);
	~Power();

	int LevelUp();

};