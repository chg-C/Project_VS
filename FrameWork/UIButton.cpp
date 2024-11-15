#include "Include.h"
#include "UIButton.h"
#define BTNRESOURCE "./resource/Img/Button/"
UIButton::UIButton(int spriteCount,bool _isSelected)
{
	isSelected = _isSelected;
	this->spriteCount = spriteCount;
	buttonSprite.resize(spriteCount);
	
}

UIButton::~UIButton()
{
}

void UIButton::Init(const char* _filename)
{
	for (int i = 0; i < spriteCount; i++)
	{
		char filename[100];
		sprintf(filename, "%s%s_%02d.png", BTNRESOURCE,_filename, i);

		// 생성한 파일 이름을 사용하여 버튼 이미지를 생성합니다.
		buttonSprite[i].Create(filename, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	curSprite = buttonSprite[0];
}
void UIButton::Update()
{
	selectArrow1.Update();
	selectArrow2.Update();
	IsSelected(isSelected);
}

void UIButton::Clicked()
{
	curSprite = buttonSprite[2];
}

void UIButton::Unclicked()
{
	curSprite = buttonSprite[0];
}

void UIButton::ButtonMouseOver()
{
	curSprite = buttonSprite[1];
}

void UIButton::ButtonRender(float x, float y, float radian, float sx, float sy, int pivotMode, const char* _text,float tx,float ty,DWORD setColor)
{
	curSprite.UIRender(x,y,radian,sx,sy,pivotMode,setColor);
	selectArrow1.Render(x - 20 - (sx / 2), y,0,1,1);
	selectArrow2.Render(x + 20 + (sx / 2), y,0,-1,1);

	char text[20];
	sprintf(text, _text);
	dv_font.DrawString(text, tx, ty);
}

bool UIButton::IsSelected(bool _isSelected)
{
	isSelected = _isSelected;
	selectArrow1.Activate(isSelected);
	selectArrow2.Activate(isSelected);
	if (isSelected)
	{
		curSprite = buttonSprite[1];
	}
	else
	{
		curSprite = buttonSprite[0];
	}
	return isSelected;
}

bool UIButton::SetIsSelected(bool value)
{
	return isSelected=value;
}
bool UIButton::GetIsSelected()
{
	return isSelected;
}