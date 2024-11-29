#include "Include.h"
#include "GameState_GameOver.h"


GameState_GameOver::GameState_GameOver()
	: gameOver(nullptr), alphaGameOverImage(0), alphaGameOverText(0)
{
	EnterState();
}

GameState_GameOver::~GameState_GameOver()
{
	ExitState();

	SAFE_DELETE(gameOver);
}

void GameState_GameOver::EnterState()
{
	gameOver = new Sprite2();
	gameOver->Create("./resource/Img/lobby/introBG.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

void GameState_GameOver::Update()
{
	if (alphaGameOverImage < 240)
	{
		alphaGameOverImage += TIME * 100;
	}
	else if (alphaGameOverText < 240)
	{
		alphaGameOverImage = 255;
		alphaGameOverText += TIME * 100;
	}
	else
	{
		alphaGameOverText = 255;
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			key.KeyTime = GetTickCount64();
			g_Mng.SwitchChapter(OVER);
		}
	}
}

void GameState_GameOver::Draw()
{
	DWORD color = 0x00ffffff;
	color |= (int)alphaGameOverImage << 24;
	gameOver->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, color, false);

	color = 0x00ff0000 | ((int)alphaGameOverText << 24);
	dv_font.DrawString("GAME OVER", 420, 300, 25, 12, 500, color);
}

void GameState_GameOver::ExitState()
{
}
