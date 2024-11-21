#include "Include.h"
#include "UIPopUp.h"

UIPopUp::UIPopUp()
{
	isOpen = false;
}
UIPopUp::~UIPopUp()
{

}

void UIPopUp::SetOpen()
{
	isOpen = true;
}

void UIPopUp::SetClose()
{
	isOpen = false;
}
void UIPopUp::Draw()
{
	frame.UIRender(480, 350, 0, 500, 580, 1);
}

bool UIPopUp::GetIsOpen()
{
	return isOpen;
}

