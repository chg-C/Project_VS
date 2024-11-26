#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp():backBtn(3,true)
{
	id = 2;

	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	UIManager::GetInstance().RegisterPopUp(id, this);


	ui.buttonMap = { { 0,{-1,-1,-1,-1} } };//�¿����
	ui.slotMap = {
		{0, {-1, 4, -1, 1}},  // ��: -1, �Ʒ�: 4, ����: -1, ������: 1
		{1, {-1, 5, 0, 2}},   // ��: -1, �Ʒ�: 5, ����: 0, ������: 2
		{2, {-1, 6, 1, 3}},   // ��: -1, �Ʒ�: 6, ����: 1, ������: 3
		{3, {-1, 7, 2, -1}},  // ��: -1, �Ʒ�: 7, ����: 2, ������: -1
		{4, {0, 8, -1, 5}},   // ��: 0, �Ʒ�: 8, ����: -1, ������: 5
		{5, {1, 9, 4, 6}},    // ��: 1, �Ʒ�: 9, ����: 4, ������: 6
		{6, {2, 10, 5, 7}},   // ��: 2, �Ʒ�: 10, ����: 5, ������: 7
		{7, {3, 11, 6, -1}},  // ��: 3, �Ʒ�: 11, ����: 6, ������: -1
		{8, {4, -1, -1, 9}},  // ��: 4, �Ʒ�: -1, ����: -1, ������: 9
		{9, {5, -1, 8, 10}},  // ��: 5, �Ʒ�: -1, ����: 8, ������: 10
		{10, {6, -1, 9, 11}}, // ��: 6, �Ʒ�: -1, ����: 9, ������: 11
		{11, {7, -1, 10, -1}} // ��: 7, �Ʒ�: -1, ����: 10, ������: -1
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
			// PowerSlot�� ����� ���� ����
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
	// ���� ���
	dv_font.DrawString("PowerUp Selection", 370, 90, 25, 12, 500);

	// �ڷΰ��� ��ư ������
	UIManager::GetInstance().GetButtons()[0].ButtonRender(680, 35, 0, 80, 50, 1, "BACK", 655, 25);

	int num = 0;
	xPos = 300;
	yPos = 190;
	xSpacing = 120;
	ySpacing = 120;

	// ���� ������
	for (int i = 0; i < 3; i++) // �� �ݺ�
	{
		for (int j = 0; j < 4; j++) // �� �ݺ�
		{
			PowerSlot* powerSlot = dynamic_cast<PowerSlot*>(ui.slots[num]); // PowerSlot���� ĳ����
			if (powerSlot)
			{
				// ���� ������ ������
				powerSlot->frame.UIRender(xPos, yPos, 0, 100, 100, 1);
				// ������ �Ŀ� ������ ������
				powerSlot->powerSprite.UIRender(xPos, yPos, 0, 45, 45, 1);
				// ���� �̸� ������
				dv_font.DrawString(powerSlot->name.c_str(), xPos - 36, yPos - 37, 13, 6, 50, D3DCOLOR_ARGB(255, 50, 50, 50));
				//// ���õ� ���� ���̶���Ʈ
				//if (powerSlot->isSelected)
				//	powerSlot->selectFrame.UIRender(xPos, yPos, 0, 110, 110, 1);
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