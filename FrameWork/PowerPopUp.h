#pragma once
#include "UIPopUp.h"
class PowerPopUp:public UIPopUp
{
	int id;
public:
	PowerPopUp();
	~PowerPopUp();
	void RenderElement() override;
};