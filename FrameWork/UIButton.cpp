#include "Include.h"
#include "UIButton.h"
#define BTNRESOURCE "./resource/Img/Button/"
UIButton::UIButton(int spriteCount,bool _isSelected,bool _isToggle)
{
	isToggle = _isToggle;
	isSelected = _isSelected;
	this->spriteCount = spriteCount;
	buttonSprite.resize(spriteCount);
	isActivated = true;

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


void UIButton::Clicked()
{
	if(!isToggle)
	if (spriteCount > 1)
	{
		curSprite = buttonSprite[2];
	}

	else if (isToggle)
	{
		if (spriteCount > 1)
		{
			curSprite = buttonSprite[1];
		}
	}
}

void UIButton::UnSelected()
{
	if (!isToggle)
	{
		curSprite = buttonSprite[0];
	}
}

void UIButton::Selected()
{
	if(!isToggle)
	if (spriteCount > 1)
	{
		curSprite = buttonSprite[1];
	}
}

void UIButton::ButtonRender(float x, float y, float radian, float sx, float sy, int pivotMode, const char* _text,float tx,float ty,DWORD setColor)
{
	if (isActivated)
	{
		curSprite.UIRender(x,y,radian,sx,sy,pivotMode,setColor);
		selectArrow1.Render(x - 20 - (sx / 2), y - 5, 0, 1, 1);
		selectArrow2.Render(x + 20 + (sx / 2), y - 5, 0, -1, 1);

		char text[20];
		sprintf(text, _text);
		dv_font.DrawString(text, tx, ty);
		IsSelected(isSelected);
		selectArrow1.Update();
		selectArrow2.Update();
	}
}

bool UIButton::IsSelected(bool _isSelected)
{
	isSelected = _isSelected;
	selectArrow1.Activate(isSelected);
	selectArrow2.Activate(isSelected);
	if (isSelected)
	{
		Selected();
	}
	else
	{
		UnSelected();
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

bool UIButton::GetActivated()
{
	return isActivated;
}

void UIButton::SetActivated(bool active)
{
	isActivated = active;
}