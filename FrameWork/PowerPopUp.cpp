#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp():backBtn(3,true)
{
	id = 2;

	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	UIManager::GetInstance().RegisterPopUp(id, this);


	ui.buttonMap = { { 0,{-1,-1,-1,-1} } };//좌우상하
	ui.slotMap = {
		{0, {-1, 4, -1, 1}},  // 위: -1, 아래: 4, 왼쪽: -1, 오른쪽: 1
		{1, {-1, 5, 0, 2}},   // 위: -1, 아래: 5, 왼쪽: 0, 오른쪽: 2
		{2, {-1, 6, 1, 3}},   // 위: -1, 아래: 6, 왼쪽: 1, 오른쪽: 3
		{3, {-1, 7, 2, -1}},  // 위: -1, 아래: 7, 왼쪽: 2, 오른쪽: -1
		{4, {0, 8, -1, 5}},   // 위: 0, 아래: 8, 왼쪽: -1, 오른쪽: 5
		{5, {1, 9, 4, 6}},    // 위: 1, 아래: 9, 왼쪽: 4, 오른쪽: 6
		{6, {2, 10, 5, 7}},   // 위: 2, 아래: 10, 왼쪽: 5, 오른쪽: 7
		{7, {3, 11, 6, -1}},  // 위: 3, 아래: 11, 왼쪽: 6, 오른쪽: -1
		{8, {4, -1, -1, 9}},  // 위: 4, 아래: -1, 왼쪽: -1, 오른쪽: 9
		{9, {5, -1, 8, 10}},  // 위: 5, 아래: -1, 왼쪽: 8, 오른쪽: 10
		{10, {6, -1, 9, 11}}, // 위: 6, 아래: -1, 왼쪽: 9, 오른쪽: 11
		{11, {7, -1, 10, -1}} // 위: 7, 아래: -1, 왼쪽: 10, 오른쪽: -1
	};


	//ui.slots.resize(12);
	//ui.slots[Might] = { "Might",0,5,200,300,false }; //name,curlevel,maxlevel,basecost,increasecost
	//ui.slots[MaxHealth] = { "Max Health",0,3,200,300,false };
	//ui.slots[Armor] = { "Armor",0,3,600,740 ,false };
	//ui.slots[Amount] = { "Amount",0,1,5000,0 ,false };
	//ui.slots[Cooldown] = { "Cooldown",0,2,900,800 ,false };
	//ui.slots[Area] = { "Area",0,2,300,660 ,false };
	//ui.slots[Velocity] = { "Velocity",0,2,300,400,false };
	//ui.slots[Duration] = { "Duration",0,2,300,400 ,false };
	//ui.slots[Speed] = { "Speed",0,2,300,400 ,false };
	//ui.slots[Magnet] = { "Magnet",0,2,300,400 ,false };
	//ui.slots[Luck] = { "Luck",0,3,600,1320 ,false };
	//ui.slots[Growth] = { "Growth",0,4,900,1000 ,false };
	ui.slots.push_back(new PowerSlot("Might", 0, 5, 200, 300)); // name, curLevel, maxLevel, baseCost, increaseCost
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
	backBtn.Init("button_c8");
	int i = 0;
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
		}
	}

	ui.buttons.push_back(backBtn);



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

	int num = 0;
	xPos = 300;
	yPos = 190;
	xSpacing = 120;
	ySpacing = 120;

	// 슬롯 렌더링
	for (int i = 0; i < 3; i++) // 행 반복
	{
		for (int j = 0; j < 4; j++) // 열 반복
		{
			PowerSlot* powerSlot = dynamic_cast<PowerSlot*>(ui.slots[num]); // PowerSlot으로 캐스팅
			if (powerSlot)
			{
				// 슬롯 프레임 렌더링
				powerSlot->frame.UIRender(xPos, yPos, 0, 100, 100, 1);
				// 슬롯의 파워 아이콘 렌더링
				powerSlot->powerSprite.UIRender(xPos, yPos, 0, 45, 45, 1);
				// 슬롯 이름 렌더링
				dv_font.DrawString(powerSlot->name.c_str(), xPos - 36, yPos - 37, 13, 6, 50, D3DCOLOR_ARGB(255, 50, 50, 50));
				//// 선택된 슬롯 하이라이트
				//if (powerSlot->isSelected)
				//	powerSlot->selectFrame.UIRender(xPos, yPos, 0, 110, 110, 1);
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
	return &ui.buttonMap;
}

std::unordered_map<int, std::tuple<int, int, int, int> >* PowerPopUp::GetSlotMap()
{
	return&ui.slotMap;
}

std::vector<UIButton>* PowerPopUp::GetButtons()
{
	return&ui.buttons;
}
std::vector<Slot*>* PowerPopUp::GetSlots()
{
	return&ui.slots;
}