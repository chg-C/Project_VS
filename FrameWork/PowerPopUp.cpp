#include "Include.h"
#include "PowerPopUp.h"

PowerPopUp::PowerPopUp():backBtn(3,true)
{
	id = 2;

	frame.Create("./resource/Img/Frame/frame.png", false, D3DCOLOR_XRGB(255, 255, 255));
	UIManager::GetInstance().RegisterPopUp(id, this);

	ui.slots[Might] = { "Might",0,5,200,300,false }; //name,curlevel,maxlevel,basecost,increasecost
	ui.slots[MaxHealth] = { "Max Health",0,3,200,300,false };
	ui.slots[Armor] = { "Armor",0,3,600,740 ,false};
	ui.slots[Amount] = { "Amount",0,1,5000,0 ,false};
	ui.slots[Cooldown] = { "Cooldown",0,2,900,800 ,false};
	ui.slots[Area] = { "Area",0,2,300,660 ,false};
	ui.slots[Velocity] = { "Velocity",0,2,300,400,false };
	ui.slots[Duration] = { "Duration",0,2,300,400 ,false };
	ui.slots[Speed] = { "Speed",0,2,300,400 ,false};
	ui.slots[Magnet] = { "Magnet",0,2,300,400 ,false};
	ui.slots[Luck] = { "Luck",0,3,600,1320 ,false};
	ui.slots[Growth] = { "Growth",0,4,900,1000 ,false};
	backBtn.Init("button_c8");

	for (int i = 0; i < TotalSlots; i++)
	{
		ui.slots[i].frame.Create("./resource/Img/Frame/frame1_c2.png",false,D3DCOLOR_XRGB(255,255,255));
	}
	ui.buttons.push_back(backBtn);

}

PowerPopUp::~PowerPopUp()
{

}

void PowerPopUp::RenderElement()
{
	dv_font.DrawString("PowerUp Selection", 370, 90, 25, 12, 500);
	int num = 0;
	xPos = 300;
	yPos = 190;
	xSpacing = 120;
	ySpacing = 120;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ui.slots[num].frame.UIRender(xPos, yPos, 0, 100, 100, 1);
			dv_font.DrawString(ui.slots[num].name.c_str(), xPos-36, yPos-30,13,6,50, D3DCOLOR_ARGB(255, 50, 50, 50));
			num++;
			xPos += xSpacing;
		}
		xPos = 300;
		yPos += ySpacing;
	}
}