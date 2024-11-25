#include "Include.h"
#include "OptionPopUp.h"

OptionPopUp::OptionPopUp() :backBtn(3, true), soundBtn(2, false, true), musicBtn(2, false, true), damageNumbersBtn(2, false, true)
{
	id = 1;
	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));

	UI.UIMap = {
		{0,{-1,-1,-1,1}},//back
		{1,{-1,-1,0,2}},//sound
		{2,{-1,-1,1,3}},//music
		{3,{-1,-1,2,-1}}//damageNumber
	};

	UIManager::GetInstance().RegisterPopUp(id, this);
	UI.optionButton.push_back(backBtn);
	UI.optionButton.push_back(soundBtn);
	UI.optionButton.push_back(musicBtn);
	UI.optionButton.push_back(damageNumbersBtn);
	UI.optionButton[0].Init("button_c8");//backBtn
	UI.optionButton[1].Init("OX_Button");//soundBtn
	UI.optionButton[2].Init("OX_Button");//musicBtn
	UI.optionButton[3].Init("OX_Button");//damageNumbersBtn
}

OptionPopUp::~OptionPopUp()
{

}

void OptionPopUp::Init()
{

}

void OptionPopUp::RenderElement()
{

		dv_font.DrawString("Options", 440,130,30,17,500);
		UIManager::GetInstance().GetButtons()[0].ButtonRender(680, 35, 0, 80, 50, 1, "BACK", 655, 25);
		UIManager::GetInstance().GetButtons()[1].ButtonRender(550, 200, 0, 50, 50, 1, "Sounds", 300, 200);
		UIManager::GetInstance().GetButtons()[2].ButtonRender(550, 350, 0, 50, 50, 1, "Music", 300, 350);
		UIManager::GetInstance().GetButtons()[3].ButtonRender(550, 500, 0, 50, 50, 1, "Damage Numbers", 300, 500);
	
}

std::unordered_map<int, std::tuple<int, int, int, int>>* OptionPopUp::GetUIMap()
{
	return &UI.UIMap;
}

std::vector<UIButton>* OptionPopUp::GetButtons()
{
	
	return &UI.optionButton;
}