#pragma once
#include "UISprite.h"

class UIPopUp:public UISprite 
{
protected:
	bool isOpen;
	UISprite frame;

public:
	UIPopUp();
	~UIPopUp();
	void SetOpen();
	void SetClose();
	void Draw();
	bool GetIsOpen();
	virtual void RenderElement() = 0;
};