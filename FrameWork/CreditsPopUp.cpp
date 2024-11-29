#include "Include.h"
#include "CreditsPopUp.h"
CreditsPopUp::CreditsPopUp():backBtn(3,true)
{
	id = 3;
	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	ui.UIMap = {
	{0,{-1,-1,-1,-1}},//back
	};
	UIManager::GetInstance().RegisterPopUp(id, this);
	ui.Buttons.push_back(backBtn);

	ui.Buttons[0].Init("button_c8");//backBtn
}

CreditsPopUp::~CreditsPopUp()
{

}

void CreditsPopUp::Init()
{

}

void CreditsPopUp::RenderElement()
{
	dv_font.DrawString("Credits", 410, 100, 30, 17, 500);
	dv_font.DrawString("���� : ����� ������ ������\n\n������Ʈ ���� : �����̾� �����̹�\n\n��� ����ϼ̽��ϴ�!", 250, 150);
	UIManager::GetInstance().GetButtons()[0].ButtonRender(680, 35, 0, 80, 50, 1, "BACK", 655, 25);
}

std::unordered_map<int, std::tuple<int, int, int, int>>* CreditsPopUp::GetButtonMap()
{
	return &ui.UIMap;
}

std::vector<UIButton>* CreditsPopUp::GetButtons()
{
	return &ui.Buttons;
}