#include "Power.h"

Power::Power(int _maxLevel)
{
	maxLevel = _maxLevel;
}
Power::~Power()
{

}

int Power::LevelUp()
{
	return curLevel++;
}