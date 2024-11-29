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
	isClicked = false;
	
}

UIButton::~UIButton()
{
}

void UIButton::Init(const char* _filename)
{
	if (!isToggle)
		spriteIdx = 0;
	else
		spriteIdx = toggleValue;
	for (int i = 0; i < spriteCount; i++)
	{
		char filename[50];
		sprintf(filename, "%s%s_%02d.png", BTNRESOURCE,_filename, i);

		// ������ ���� �̸��� ����Ͽ� ��ư �̹����� �����մϴ�.
		buttonSprite[i].Create(filename, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	sound.EffectSoundRegister("./resource/Sound/Click.mp3", "Click");
}

void UIButton::Clicked()
{

	if (!isToggle)
	{
		if (spriteCount > 2)
		{
			spriteIdx = 2;
			isClicked = true;           // Ŭ�� ���� Ȱ��ȭ
		}
	}
	sound.EffectSoundPlay("Click");
			
}

void UIButton::UnSelected()
{
	isClicked = false;
	if (!isToggle)
	{
		if (!isClicked) // Ŭ�� ���°� �ƴϸ� �⺻ ���·� ����
		{
			spriteIdx = 0;
		}
	}
}

void UIButton::Selected()
{
	if (!isToggle)
	{
		if (spriteCount > 1 && !isClicked) // Ŭ���� ���°� �ƴϸ� ���� ���·� ����
		{
			spriteIdx = 1;
		}
	}
}

void UIButton::ButtonRender(float x, float y, float radian, float sx, float sy, int pivotMode, const char* _text,float tx,float ty,DWORD setColor)
{
	if (isActivated)
	{
		if (isToggle)
			curSprite = buttonSprite[toggleValue];
		else
			curSprite = buttonSprite[spriteIdx];
		curSprite.UIRender(x,y,radian,sx,sy,pivotMode,setColor);
		selectArrow1.Render(x - 20 - (sx / 2), y - 5, 0, 1, 1);
		selectArrow2.Render(x + 20 + (sx / 2), y - 5, 0, -1, 1);

		char text[20];
		sprintf(text, _text);
		dv_font.DrawString(text, tx, ty);
		IsSelected(isSelected);

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

void UIButton::SetClicked(bool value)
{
	isClicked = value;

	// Ŭ�� ���°� �����Ǹ� ��������Ʈ �ʱ�ȭ
	if (!isClicked)
	{
		curSprite = buttonSprite[isSelected ? 1 : 0];
	}
}

bool UIButton::GetIsToggle()
{
	return isToggle;
}

bool UIButton::GetToggleValue()
{
	return toggleValue;
}

void UIButton::SetToggleValue(bool val)
{
	toggleValue = val;
}