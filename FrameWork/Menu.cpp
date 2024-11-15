#include "Include.h"
static DWORD KeyTime = GetTickCount();
Menu::Menu():startBtn(3,true),collectBtn(3,false),achievementsBtn(3,false)
{
	menuBtn.push_back(startBtn);
	menuBtn.push_back(collectBtn);
	menuBtn.push_back(achievementsBtn);
}

Menu::~Menu()
{
}

void Menu::Init()
{
	count = 0;
	alpha = 0;
	introBG.Create("./resource/Img/lobby/introBG.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust00.Create("./resource/Img/lobby/illustrations_0.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust01.Create("./resource/Img/lobby/illustrations_1.png", false, D3DCOLOR_XRGB(0, 0, 0));
	introillust02.Create("./resource/Img/lobby/illustrations_2.png", false, D3DCOLOR_XRGB(0, 0, 0));
	menuBtn[0].Init("button_c9");
	menuBtn[1].Init("button_c9");
	menuBtn[2].Init("button_c9");
	
}	

// Chap, 재정의 함수 호출
void Menu::Update(double frame)
{
	menuBtn[0].Update();
	menuBtn[1].Update();
	menuBtn[2].Update();	//key.Update();

	//if (xx.xxx > 100 * xxx.xxx)
	//{
	//	if (GetTickCount() - CoinTime > 100)
	//	{
	//		count++;
	//		CoinTime = GetTickCount();
	//	}
	//	if (count > 1) count = 0;
	//}
}

void Menu::Draw()
{
	introBG.UIRender(0, 0, 0, 960, 640,0); //이미지출력
	introillust02.UIRender(950, 100, 0, -422, 398,0, 0x90ffffff);
	introillust01.UIRender(80, 80, 0, 390, 564,0, 0x80ffffff);
	introillust00.UIRender(480, 500, 0, 642,378,1);
	menuBtn[0].ButtonRender(480, 450, 0, 200, 70, 1,"START",450,440);
	menuBtn[1].ButtonRender(300, 520, 0, 200, 50, 1, "COLLECTION",245,510);
	menuBtn[2].ButtonRender(670, 520, 0, 200, 50, 1, "ACHIEVEMENTS", 600, 510);
	
}

void Menu::OnMessage(MSG* msg)
{
	//char aaa[256];
	//_itoa_s(msg->message, aaa,2);
	//dv_font.DrawString(aaa, 10 , 210 ) ;   
	//PostQuitMessage(0);

	switch (msg->message)
	{
		case WM_KEYDOWN:
		{
		switch (msg->wParam)
			{
			case VK_F12:
				//MessageBox(NULL, "", "", 0);
				if (g_Mng.n_Chap = MENU)
				{

					g_Mng.n_Chap = GAME;
					sound.m_Bk1->Play(0, DSBPLAY_LOOPING);
					
				}
				break;

			}
		}
		case WM_CHAR:
			switch (msg->wParam)
			{
			case VK_DOWN:
				if (buttonIdx < 2 && buttonIdx >= 0)
				{
					menuBtn[buttonIdx].SetIsSelected(false);
					buttonIdx++;
					menuBtn[buttonIdx].SetIsSelected(true);
				}
				break;
			case VK_UP:
				if (buttonIdx < 3 && buttonIdx > 0)
				{
					menuBtn[buttonIdx].SetIsSelected(false);
					buttonIdx--;
					menuBtn[buttonIdx].SetIsSelected(true);
				}
				break;
			case VK_RETURN:
				for (int i = 0; i < menuBtn.size(); i++)
				{
					if (menuBtn[i].GetIsSelected())
					{
						menuBtn[i].Clicked();
						if (buttonIdx == 0)
						{
							g_Mng.n_Chap = GAME;
							//sound.m_Bk1->Play(0, DSBPLAY_LOOPING);
						}
					}
				}
				break;
			}
	}
}