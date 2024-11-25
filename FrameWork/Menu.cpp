#include "Include.h"
static DWORD KeyTime = GetTickCount();

Menu::Menu():optionBtn(3,false), startBtn(3, true), collectBtn(3, false),powerupBtn(3,false), achievementsBtn(3, false),creditsBtn(3,false)
{
	isPopUpOpen = false;
	curPopUpIdx = 0;
	UI.buttonMap = {
		{0,{-1,-1,-1,1}},//option: 왼쪽 없음 오른쪽 없음
		{1,{2,4,0,3}},//start: 왼쪽 없음 오른쪽 없음
		{2,{-1,3,1,5}},//collect: 왼쪽 없음 오른쪽 power
		{3,{2,4,1,5}},//power : 왼쪽 collect 오른쪽 achieve
		{4,{3,-1,1,5}},//achieve: 왼쪽 power 오른쪽 없음
		{5,{2,4,3,-1}}//credits : 왼쪽 없음 오른쪽 없음
	};

	buttonIdx = 1;
	UI.menuBtn.push_back(optionBtn);		//buttonIdx 0
	UI.menuBtn.push_back(startBtn);			//buttonIdx 1
	UI.menuBtn.push_back(collectBtn);		//buttonIdx 2
	UI.menuBtn.push_back(powerupBtn);		//buttonIdx 3
	UI.menuBtn.push_back(achievementsBtn);	//buttonIdx 4
	UI.menuBtn.push_back(creditsBtn);		//buttonIdx 5
}

Menu::~Menu()
{
}

void Menu::Init()
{
	count = 0;
	alpha = 0;
	introBG.Create("./resource/Img/lobby/introBG.png", false, D3DCOLOR_XRGB(0, 0, 0));
	title.Create("./resource/Img/lobby/title.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust00.Create("./resource/Img/lobby/illustrations_0.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust01.Create("./resource/Img/lobby/illustrations_1.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust02.Create("./resource/Img/lobby/illustrations_2.png", false, D3DCOLOR_XRGB(0, 0, 0));
	//UI.menuBtn[0].Init("button_c9");
	//UI.menuBtn[1].Init("button_c9");
	//UI.menuBtn[2].Init("button_c9");
	//UI.menuBtn[3].Init("button_c5");
	//UI.menuBtn[4].Init("button_c9");
	//UI.menuBtn[5].Init("button_c9");
	
	UI.menuBtn[0].Init("button_c9");
	UI.menuBtn[1].Init("button_c9");
	UI.menuBtn[2].Init("button_c9");
	UI.menuBtn[3].Init("button_c5");
	UI.menuBtn[4].Init("button_c9");
	UI.menuBtn[5].Init("button_c9");

	UIManager::GetInstance().SetButtonMap(UI.buttonMap);
	UIManager::GetInstance().SetButtons(UI.menuBtn);
}	

// Chap, 재정의 함수 호출
void Menu::Update(double frame)
{

}

void Menu::Draw()
{
	introBG.UIRender(0, 0, 0, 960, 640,0); //이미지출력
	introillust02.UIRender(950, 100, 0, -422, 398,0, 0x90ffffff);
	introillust01.UIRender(20, 30, 0, 429, 620.4,0, 0x80ffffff);
	introillust00.UIRender(480, 500, 0, 642,378,1);
	title.UIRender(480, 200, 0, 400, 400, 1);
	//UI.menuBtn[0].ButtonRender(700, 25, 0, 100, 50, 1, "OPTIONS", 660, 15);
	//UI.menuBtn[1].ButtonRender(480, 450, 0, 200, 70, 1,"START",450,440);
	//UI.menuBtn[2].ButtonRender(250, 520, 0, 200, 50, 1, "COLLECTION",195,510);
	//UI.menuBtn[3].ButtonRender(480, 520, 0, 200, 50, 1, "POWERUP", 435, 510);
	//UI.menuBtn[4].ButtonRender(720, 520, 0, 200, 50, 1, "ACHIEVEMENTS", 650, 510);
	//UI.menuBtn[5].ButtonRender(480, 600, 0, 190, 30, 1, "CREDITS", 435, 595);
	if (!isPopUpOpen)
	{
		UIManager::GetInstance().GetButtons()[0].ButtonRender(700, 25, 0, 100, 50, 1, "OPTIONS", 660, 15,0xffffffff);
		UIManager::GetInstance().GetButtons()[1].ButtonRender(480, 450, 0, 200, 70, 1, "START", 450, 440);
		UIManager::GetInstance().GetButtons()[2].ButtonRender(250, 520, 0, 200, 50, 1, "COLLECTION", 195, 510);
		UIManager::GetInstance().GetButtons()[3].ButtonRender(480, 520, 0, 200, 50, 1, "POWERUP", 435, 510);
		UIManager::GetInstance().GetButtons()[4].ButtonRender(720, 520, 0, 200, 50, 1, "ACHIEVEMENTS", 650, 510);
		UIManager::GetInstance().GetButtons()[5].ButtonRender(480, 600, 0, 190, 30, 1, "CREDITS", 435, 595);
	}
	else if (UIManager::GetInstance().GetPopUp(1)->GetIsOpen())
	{
		curPopUp->Draw();
		curPopUp->RenderElement();
	}
	else if (UIManager::GetInstance().GetPopUp(2)->GetIsOpen())
	{
		curPopUp->Draw();
		curPopUp->RenderElement();
	}
	
}

void Menu::OnMessage(MSG* msg)
{
	static bool wasReturnPressed = false; // VK_RETURN 이전 상태
	switch (msg->message)
	{
		case WM_KEYDOWN:
		case WM_CHAR:
			switch (msg->wParam)
			{
			case VK_DOWN:
				if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
				if (UIManager::GetInstance().GetButtonMap().count(buttonIdx) > 0 && GetTickCount64() - KeyTime > 200) {
					KeyTime = GetTickCount64();
					int newIdx = std::get<3>(UIManager::GetInstance().GetButtonMap()[buttonIdx]); // 아래쪽 버튼 인덱스 가져오기
					if (newIdx >= 0) {
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(false);
						buttonIdx = newIdx;
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(true);
						break;
					}
				}
				break;

			case VK_UP:
				if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
				if (UIManager::GetInstance().GetButtonMap().count(buttonIdx) > 0 && GetTickCount64() - KeyTime > 100) {
					KeyTime = GetTickCount64();
					int newIdx = std::get<2>(UIManager::GetInstance().GetButtonMap()[buttonIdx]); // 위쪽 버튼 인덱스 가져오기
					if (newIdx >= 0) {
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(false);
						buttonIdx = newIdx;
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(true);
					}
				}
				break;

			case VK_LEFT:  // 좌 방향키 처리
				if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
				if (UIManager::GetInstance().GetButtonMap().count(buttonIdx) > 0 && GetTickCount64() - KeyTime > 100) {
					KeyTime = GetTickCount64();
					int newIdx = std::get<0>(UIManager::GetInstance().GetButtonMap()[buttonIdx]); // 왼쪽 버튼 인덱스 가져오기
					if (newIdx >= 0) {
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(false);
						buttonIdx = newIdx;
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(true);
					}
				}
				break;

			case VK_RIGHT:  // 우 방향키 처리
				if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
				if (UIManager::GetInstance().GetButtonMap().count(buttonIdx) > 0 && GetTickCount64() - KeyTime > 100) {
					KeyTime = GetTickCount64();
					int newIdx = std::get<1>(UIManager::GetInstance().GetButtonMap()[buttonIdx]); // 오른쪽 버튼 인덱스 가져오기
					if (newIdx >= 0) {
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(false);
						buttonIdx = newIdx;
						UIManager::GetInstance().GetButtons()[buttonIdx].SetIsSelected(true);
					}
				}
				break;
			case VK_RETURN:
					if(UIManager::GetInstance().GetButtons()[buttonIdx].GetIsToggle() == false)
						UIManager::GetInstance().GetButtons()[buttonIdx].Clicked();
					wasReturnPressed = true;
				break;
			case VK_ESCAPE:
				ClosePopUp();
				break;
			}
			break;
		case WM_KEYUP:  // 키를 뗐을 때 처리
			if (msg->wParam == VK_RETURN)
			{
				if (wasReturnPressed)
				{
					UIManager::GetInstance().GetButtons()[buttonIdx].SetClicked(false);
					switch (curPopUpIdx)
					{
					case 0:
						MenuInput();
						wasReturnPressed = false;
						break;
					case 1:
						OptionInput();
						wasReturnPressed = false;
						break;
					}
				}
			}
	}
}

void Menu::AllButtonActivated(bool value)
{
	for (UIButton& button : UIManager::GetInstance().GetButtons())
	{
		button.SetActivated(value);
	}
}

void Menu::OpenPopUp(int id)
{
	isPopUpOpen = true;
	if (!UIManager::GetInstance().GetPopUp(id)->GetIsOpen())
	{
		UIManager::GetInstance().OpenPopUp(id);
		AllButtonActivated(false);
		curPopUp = UIManager::GetInstance().GetPopUp(id);
	}
	curPopUpIdx = id;
}

void Menu::ClosePopUp()
{
	buttonIdx = 1;
	UIManager::GetInstance().GetButtons()[buttonIdx].SetClicked(false);
	for (int i = 1; i <= UIManager::GetInstance().GetPopUPCount(); i++)
	{
		if (UIManager::GetInstance().GetPopUp(i)->GetIsOpen())
		{
			UIManager::GetInstance().ClosePopUp(i);
			UIManager::GetInstance().SetButtonMap(UI.buttonMap);
			UIManager::GetInstance().SetButtons(UI.menuBtn);
			AllButtonActivated(true);
			isPopUpOpen = false;
			curPopUpIdx = 0;
		}
	}
}

void Menu::MenuInput()
{
	if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
		for (int i = 0; i < UIManager::GetInstance().GetButtons().size(); i++)
		{
			if (UIManager::GetInstance().GetButtons()[i].GetActivated() && UIManager::GetInstance().GetButtons()[i].GetIsSelected())
			{
				if (buttonIdx == 0)
				{
					OpenPopUp(1);
					UIManager::GetInstance().SetButtonMap(*curPopUp->GetUIMap());
					UIManager::GetInstance().SetButtons(*curPopUp->GetButtons());
					break;
				}
				else if (buttonIdx == 1)
				{
					g_Mng.n_Chap = GAME;
				}
				else if (buttonIdx == 3)
				{
					OpenPopUp(2);
				}
			}
		}
}

void Menu::OptionInput()
{
	if (UIManager::GetInstance().GetButtons()[buttonIdx].GetActivated())
		for (int i = 0; i < UIManager::GetInstance().GetButtons().size(); i++)
		{
			if (UIManager::GetInstance().GetButtons()[i].GetActivated() && UIManager::GetInstance().GetButtons()[i].GetIsSelected())
			{
				if (buttonIdx == 0)
				{
					ClosePopUp();
				}
				else if (buttonIdx == 1)
				{
					UIManager::GetInstance().GetButtons()[buttonIdx].Clicked();
					
				}
				else if (buttonIdx == 2)
				{
					UIManager::GetInstance().GetButtons()[buttonIdx].Clicked();
				}
				else if (buttonIdx == 3)
				{
					UIManager::GetInstance().GetButtons()[buttonIdx].Clicked();
				}
			}
		}
}