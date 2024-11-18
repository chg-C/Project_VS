#pragma once
#include "UIPopUp.h"
class Option :public UIPopUp
{
protected:
	UIButton exitBtn;
public:
	Option();
	~Option();
	void Open();
	void Close();
};
