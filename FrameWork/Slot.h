#pragma once
#include "UISprite.h"
class Slot
{
protected:
	UISprite frame;
	UISprite selectFrame;
	bool isSelected = false;
	friend class PowerPopUp;
public:
	Slot() {}
	virtual ~Slot() {}

	void SetSelected(bool value)
	{
		isSelected = value;
	}
	bool GetSelected()
	{
		return isSelected;
	}
	UISprite GetSelectFrame()
	{
		return selectFrame;
	}
};
