#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp():backBtn(3,true)
{
	id = 2;

	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	
	UIManager::GetInstance().RegisterPopUp(id, this);


	ui.UIMap = {
		{0,{-1,-1,12,1}},
		{1, {4, 2, 0, 5}},    // ����: -1, ������: 2, ��: -1, �Ʒ�: 5
		{2, {1, 3, 0, 6}},     // ����: 1, ������: 3, ��: -1, �Ʒ�: 6
		{3, {2, 4, 0, 7}},     // ����: 2, ������: 4, ��: -1, �Ʒ�: 7
		{4, {3, 1, 0, 8}},    // ����: 3, ������: -1, ��: -1, �Ʒ�: 8
		{5, {8, 6, 1, 9}},     // ����: -1, ������: 6, ��: 1, �Ʒ�: 9
		{6, {5, 7, 2, 10}},     // ����: 5, ������: 7, ��: 2, �Ʒ�: 10
		{7, {6, 8, 3, 11}},     // ����: 6, ������: 8, ��: 3, �Ʒ�: 11
		{8, {7, 5, 4, 12}},    // ����: 7, ������: -1, ��: 4, �Ʒ�: 12
		{9, {12, 10, 5, 0}},   // ����: -1, ������: 10, ��: 5, �Ʒ�: -1
		{10, {9, 11, 6, 0}},   // ����: 9, ������: 11, ��: 6, �Ʒ�: -1
		{11, {10, 12, 7, 0}},  // ����: 10, ������: 12, ��: 7, �Ʒ�: -1
		{12, {11, 9, 8, 0}}   // ����: 11, ������: -1, ��: 8, �Ʒ�: -1
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
			// PowerSlot�� ����� ���� ����
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

	// ���� ���
	dv_font.DrawString("PowerUp Selection", 370, 90, 25, 12, 500);

	// �ڷΰ��� ��ư ������
	UIManager::GetInstance().GetButtons()[0].ButtonRender(680, 35, 0, 80, 50, 1, "BACK", 655, 25);

	int num = 1;
	xPos = 300;
	yPos = 190;
	xSpacing = 120;
	ySpacing = 120;

	// ���� ������
	for (int i = 0; i < 3; i++) // �� �ݺ�
	{
		for (int j = 0; j < 4; j++) // �� �ݺ�
		{
			int lvXPos = 0;
			PowerSlot* powerSlot = dynamic_cast<PowerSlot*>(ui.slots[num]); // PowerSlot���� ĳ����
			if (powerSlot)
			{
				// ���� ������ ������
				powerSlot->frame.UIRender(xPos, yPos, 0, 100, 100, 1);
				// ���� �Ŀ� ������ ������
				powerSlot->powerSprite.UIRender(xPos, yPos, 0, 45, 45, 1);
				// ���� �̸� ������
				dv_font.DrawString(powerSlot->name.c_str(), xPos - 36, yPos - 37, 13, 6, 50, D3DCOLOR_ARGB(255, 50, 50, 50));
				//���� ���� ������ ������
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

				//// ���õ� ���� ���̶���Ʈ
				if (UIManager::GetInstance().GetSlots()[num]->GetSelected())
					UIManager::GetInstance().GetSlots()[num]->GetSelectFrame().UIRender(xPos, yPos, 0, 110, 110, 1);
			}
			num++;
			xPos += xSpacing; // ���� �������� X ��ġ �̵�
		}

		xPos = 300; // ���� ���� X ��ġ �ʱ�ȭ
		yPos += ySpacing; // Y ��ġ �̵�
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