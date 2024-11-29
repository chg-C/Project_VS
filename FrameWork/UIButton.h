#pragma once
#include "UISprite.h"
#include "SelectArrow.h"
#include <vector>
#include "SoundInterface.h"
class UIButton
{
	int buttonId;
	int spriteCount;
	int spriteIdx;

	bool isToggle;
	bool isClicked;
	bool isSelected;
	bool isActivated;

	bool toggleValue;

	std::vector<UISprite> buttonSprite;
	UISprite curSprite;
	SelectArrow selectArrow1;
	SelectArrow selectArrow2;

	SoundInterface sound;

public:
	UIButton(int spriteCount, bool _isSelected, bool isToggle = false);
	~UIButton();
	void Init(const char* _filename);
	void Clicked();
	void UnSelected();
	void Selected();
	void ButtonRender(float x, float y, float radian, float sx, float sy, int pivotMode,const char* _text ,float tx,float ty,DWORD setColor = 0xffffffff);
	bool IsSelected(bool isSelected);
	bool SetIsSelected(bool);
	bool GetIsSelected();
	bool GetActivated();
	void SetActivated(bool active);
	void SetClicked(bool value);
	bool GetIsToggle();
	bool GetToggleValue();
	void SetToggleValue(bool value);
};
