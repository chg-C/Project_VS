#define _CRT_NONSTDC_NO_DEPRECATE

#include "Include.h"
#include "Sprite2.h"

Logo::Logo()
{
	loadimg = new Sprite2();
	loadimg2 = new Sprite2();
	square = new Sprite2();

	sprintf_s(loadingText, "Now Loading");
}

Logo::~Logo()
{
	SAFE_DELETE(loadimg);
	SAFE_DELETE(loadimg2);
}

void Logo::Init()
{
	speed = 2000;
	alpha = 0;

	loadimg->Create("./resource/Img/lobby/introBG.png", false);
	loadimg2->Create("./resource/Img/lobby/title.png", false);
	square->Create("./resource/Img/Etc/square.png", false);
}

// Chap, 재정의 함수 호출
void Logo::Update(double frame)
{
	float factor = 2000;
	if (alpha < 50)
	{
		sprintf_s(loadingText, "Loading Textures");
	}
	else if (alpha < 150)
	{
		factor = 3000;
		sprintf_s(loadingText, "Loading Character Datas");
	}
	else if (alpha < 200)
	{
		factor = 4500;
		sprintf_s(loadingText, "Loading Enemy Datas");
	}
	else
	{
		factor = 6000;
		sprintf_s(loadingText, "Loading Weapon Datas");
	}
	
	alpha += speed * frame / factor;

	if(alpha >= 254) {
		g_Mng.SwitchChapter(MENU);
	}	
}

void Logo::Draw()
{
	//loadimg.SetColor(255,255,255, alpha);  // 색상 변경
	//loadimg.Draw( 350 , 100 ) ;  //이미지출력
	DWORD color = 0x00ffffff;
	color |= (int)alpha << 24;
	
	loadimg->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, 0xffffffff, false);
	loadimg2->DrawStretch(480, 200, 400, 400, color, false, 0, PIVOT_CENTER);

	float gaugeSize = SCREEN_WITH - 200 - 10;

	square->DrawStretch(100, SCREEN_HEIGHT - 100, gaugeSize + 10, 50, 0xff000000);

	gaugeSize /= 255;
	gaugeSize *= alpha;
	square->DrawStretch(105, SCREEN_HEIGHT - 95, gaugeSize, 40, 0xffffffff);

	int len = strlen(loadingText);
	dv_font.DrawString(loadingText, (SCREEN_WITH / 2) - (len * 12 / 2), SCREEN_HEIGHT - 140);
	//dv_font.DrawString( "로고" , 200 , 210 ) ;   //글자출력
}

void Logo::OnMessage( MSG* msg )
{
	switch(msg->message)
	{
	case WM_LBUTTONDOWN :

		break;
	}

}