#include "Include.h"
#include "Score.h"

Over::Over()
{
	loadimg = new Sprite2();
}

Over::~Over()
{
	delete loadimg;
}

void Over::Init()
{
	loadimg->Create("./resource/Img/lobby/introBG.png", false);
}

// Chap, 재정의 함수 호출
void Over::Update(double frame)
{
	//if(처리 후) g_Mng.n_Chap = MENU; 
	if (KeyDown(VK_RETURN) && GetTickCount64() - key.KeyTime > 1000)
	{
		GameManager::GetInstance().GameReset();
		g_Mng.SwitchChapter(MENU);
	}
}

void Over::Draw()
{
	loadimg->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, 0xffffffff, false);
	int killScore = Score::GetInstance().GetKillCount();
	char scoreText[60] = {};
	sprintf_s(scoreText, "%s %d", "Kill Count : ", killScore);

	dv_font.DrawString(scoreText, 420, 250);


	dv_font.DrawString("Press any key", 420, 300);

}

void Over::OnMessage(MSG* msg)
{

}