#pragma once
#include "UISprite.h"
class Slot
{
protected:
	UISprite frame;

	friend class PowerPopUp;
public:
	Slot() {}
	~Slot() {}
};
