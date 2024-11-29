#include "Include.h"
#include "GameState_Clear.h"

GameState_Clear::GameState_Clear(Enemy* boss)
	: gameOver(nullptr), alphaGameOverImage(0), alphaGameOverText(0), boss(boss)
{
	EnterState();
}

GameState_Clear::~GameState_Clear()
{
	ExitState();
	SAFE_DELETE(gameOver);
}

void GameState_Clear::EnterState()
{
	gameOver = new Sprite2();
	gameOver->Create("./resource/Img/lobby/introBG.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

void GameState_Clear::Update()
{
	if (boss->GetState() != CS_DEAD)
	{
		boss->Update();
	}
	else if (alphaGameOverImage < 120)
	{
		alphaGameOverImage += TIME * 100;
	}
	else if (alphaGameOverText < 240)
	{
		alphaGameOverImage = 128;
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

void GameState_Clear::Draw()
{
	DWORD color = 0x00ffffff;
	color |= (int)alphaGameOverImage << 24;
	gameOver->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, color, false);

	color = 0x00ffffff | ((int)alphaGameOverText << 24);
	dv_font.DrawString("GAME CLEAR!", 420, 300, 25, 12, 500, color);
}

void GameState_Clear::ExitState()
{
}
