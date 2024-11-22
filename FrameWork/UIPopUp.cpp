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

std::unordered_map<int, std::tuple<int, int, int, int>>* UIPopUp::GetButtonMap()
{
	return nullptr;
}
std::vector<UIButton>* UIPopUp::GetButtons()
{
	return nullptr;
}