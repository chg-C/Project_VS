#pragma once
#include "UISprite.h"
#include "SelectArrow.h"
#include <vector>
class UIButton
{
	static int Id;
	int buttonId;
	int spriteCount;
	bool isSelected;
	bool isActivated;
	std::vector<UISprite> buttonSprite;
	UISprite curSprite;
	SelectArrow selectArrow1;
	SelectArrow selectArrow2;
public:
	UIButton(int spriteCount,bool _isSelected);
	~UIButton();
	void Init(const char* _filename);
	void Clicked();
	void Unclicked();
	void ButtonMouseOver();
	void Update();
	void ButtonRender(float x, float y, float radian, float sx, float sy, int pivotMode,const char* _text ,float tx,float ty,DWORD setColor = 0xffffffff);
	bool IsSelected(bool isSelected);
	bool SetIsSelected(bool);
	bool GetIsSelected();
	bool GetActivated();
	void SetActivated(bool active);
};
