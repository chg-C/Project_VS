#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp():backBtn(3,true)
{
	id = 2;

	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	
	UIManager::GetInstance().RegisterPopUp(id, this);


	ui.UIMap = {
		{0,{-1,-1,12,1}},
		{1, {4, 2, 0, 5}},    // 왼쪽: -1, 오른쪽: 2, 위: -1, 아래: 5
		{2, {1, 3, 0, 6}},     // 왼쪽: 1, 오른쪽: 3, 위: -1, 아래: 6
		{3, {2, 4, 0, 7}},     // 왼쪽: 2, 오른쪽: 4, 위: -1, 아래: 7
		{4, {3, 1, 0, 8}},    // 왼쪽: 3, 오른쪽: -1, 위: -1, 아래: 8
		{5, {8, 6, 1, 9}},     // 왼쪽: -1, 오른쪽: 6, 위: 1, 아래: 9
		{6, {5, 7, 2, 10}},     // 왼쪽: 5, 오른쪽: 7, 위: 2, 아래: 10
		{7, {6, 8, 3, 11}},     // 왼쪽: 6, 오른쪽: 8, 위: 3, 아래: 11
		{8, {7, 5, 4, 12}},    // 왼쪽: 7, 오른쪽: -1, 위: 4, 아래: 12
		{9, {12, 10, 5, 0}},   // 왼쪽: -1, 오른쪽: 10, 위: 5, 아래: -1
		{10, {9, 11, 6, 0}},   // 왼쪽: 9, 오른쪽: 11, 위: 6, 아래: -1
		{11, {10, 12, 7, 0}},  // 왼쪽: 10, 오른쪽: 12, 위: 7, 아래: -1
		{12, {11, 9, 8, 0}}   // 왼쪽: 11, 오른쪽: -1, 위: 8, 아래: -1
	};

	ui.slots.push_back(nullptr);
	ui.slots.push_back(new PowerSlot("Might",0, 5, 200, 300)); // name, curLevel, maxLevel, baseCost, increaseCost
	ui.slots.push_back(new PowerSlot("Max Health", 0, 3, 200, 300));
	ui.slots.push_back(new PowerSlot("Armor", 0, 3, 600, 740));
	ui.slots.push_back(new PowerSlot("Amount", 0, 1, 5000, 0));
	ui.slots.push_back(new PowerSlot("Cooldown", 0, 2, 900, 800));
	ui.slots.push_back(new PowerSlot("Area", 0, 2, 300, 660));
	ui.slots.push_back(new PowerSlot("Velocity", 0, 2, 300, 400));
	ui.slots.push_back(new PowerSlot("Duration", 0, 2, 300, 400));
	ui.slots.push_back(new PowerSlot("Speed", 0, 2, 300, 400));
	ui.slots.push_back(new PowerSlot("Magnet", 0, 2, 300, 400));
	ui.slots.push_back(new PowerSlot("Luck", 0, 3, 600, 1320));
	ui.slots.push_back(new PowerSlot("Growth", 0, 4, 900, 1000));
	int i = 1;
	for (Slot* slot : ui.slots)
	{
		PowerSlot* powerSlot = dynamic_cast<PowerSlot*>(slot);
		if (powerSlot)
		{
			powerSlot->spritePath = "./resource/Img/power/" + std::to_string(i) + ".png";
			i++;
			// PowerSlot의 멤버에 접근 가능
			powerSlot->powerSprite.Create(powerSlot->spritePath.c_str(), false, D3DCOLOR_XRGB(255, 255, 255));
			slot->frame.Create("./resource/Img/Frame/frame1_c2.png", false, D3DCOLOR_XRGB(255, 255, 255));
			slot->selectFrame.Create("./resource/Img/Frame/select.png", false, D3DCOLOR_XRGB(255, 255, 255));
			powerSlot->LevelSprite[0].Create("./resource/Img/Frame/PLvFrame0.png",false, D3DCOLOR_XRGB(255, 255, 255));
			powerSlot->LevelSprite[1].Create("./resource/Img/Frame/PLvFrame1.png", false, D3DCOLOR_XRGB(255, 255, 255));
		}
	}

	

	ui.buttons.push_back(backBtn);
	ui.buttons[0].Init("button_c8");


}

PowerPopUp::~PowerPopUp()
{

}

void PowerPopUp::RenderElement()
{

	// 제목 출력
	dv_font.DrawString("PowerUp Selection", 370, 90, 25, 12, 500);

	// 뒤로가기 버튼 렌더링
	UIManager::GetInstance().GetButtons()[0].ButtonRender(680, 35, 0, 80, 50, 1, "BACK", 655, 25);

	int num = 1;
	xPos = 300;
	yPos = 190;
	xSpacing = 120;
	ySpacing = 120;

	// 슬롯 렌더링
	for (int i = 0; i < 3; i++) // 행 반복
	{
		for (int j = 0; j < 4; j++) // 열 반복
		{
			int lvXPos = 0;
			PowerSlot* powerSlot = dynamic_cast<PowerSlot*>(ui.slots[num]); // PowerSlot으로 캐스팅
			if (powerSlot)
			{
				// 슬롯 프레임 렌더링
				powerSlot->frame.UIRender(xPos, yPos, 0, 100, 100, 1);
				// 슬롯 파워 아이콘 렌더링
				powerSlot->powerSprite.UIRender(xPos, yPos, 0, 45, 45, 1);
				// 슬롯 이름 렌더링
				dv_font.DrawString(powerSlot->name.c_str(), xPos - 36, yPos - 37, 13, 6, 50, D3DCOLOR_ARGB(255, 50, 50, 50));
				//슬롯 레벨 프레임 렌더링
				for (int i = 0; i < powerSlot->maxLevel; i++)
				{
					if (powerSlot->maxLevel == 5)
					{
						if (i < powerSlot->curLevel)
							powerSlot->LevelSprite[1].UIRender((xPos - 30) + lvXPos, yPos + 30, 0, 15, 15, 1);
						else
							powerSlot->LevelSprite[0].UIRender((xPos - 30) + lvXPos, yPos + 30, 0, 15, 15, 1);
					}
					else if (powerSlot->maxLevel == 4)
					{
						if (i < powerSlot->curLevel)
							powerSlot->LevelSprite[1].UIRender((xPos - 20) + lvXPos, yPos + 30, 0, 15, 15, 1);
						else
							powerSlot->LevelSprite[0].UIRender((xPos - 20) + lvXPos, yPos + 30, 0, 15, 15, 1);
					}

					else if (powerSlot->maxLevel == 3)
					{
						if (i < powerSlot->curLevel)
							powerSlot->LevelSprite[1].UIRender((xPos-15) + lvXPos, yPos + 30, 0, 15, 15, 1);
						else
							powerSlot->LevelSprite[0].UIRender((xPos - 15) + lvXPos, yPos + 30, 0, 15, 15, 1);

					}

					else if (powerSlot->maxLevel == 2)
					{
						if (i < powerSlot->curLevel)
							powerSlot->LevelSprite[1].UIRender((xPos - 7) + lvXPos, yPos + 30, 0, 15, 15, 1);
						else
							powerSlot->LevelSprite[0].UIRender((xPos - 7) + lvXPos, yPos + 30, 0, 15, 15, 1);
					}

					else
					{
						if (i < powerSlot->curLevel)
							powerSlot->LevelSprite[1].UIRender((xPos) + lvXPos, yPos + 30, 0, 15, 15, 1);
						else
							powerSlot->LevelSprite[0].UIRender((xPos)+lvXPos, yPos + 30, 0, 15, 15, 1);

					}
					lvXPos += 15;
				}

				//// 선택된 슬롯 하이라이트
				if (UIManager::GetInstance().GetSlots()[num]->GetSelected())
					UIManager::GetInstance().GetSlots()[num]->GetSelectFrame().UIRender(xPos, yPos, 0, 110, 110, 1);
			}
			num++;
			xPos += xSpacing; // 다음 슬롯으로 X 위치 이동
		}

		xPos = 300; // 다음 행의 X 위치 초기화
		yPos += ySpacing; // Y 위치 이동
	}
}


std::unordered_map<int, std::tuple<int, int, int, int> >* PowerPopUp::GetButtonMap()
{
	return &ui.UIMap;
}

std::vector<UIButton>* PowerPopUp::GetButtons()
{
	return&ui.buttons;
}
std::vector<Slot*>* PowerPopUp::GetSlots()
{
	return&ui.slots;
}