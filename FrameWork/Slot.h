#pragma once
#include "UISprite.h"
class Slot
{
protected:
	UISprite frame;
	UISprite selectFrame;
	bool isSelected;
	friend class PowerPopUp;
public:
	Slot() {}
	virtual ~Slot() {}
};
