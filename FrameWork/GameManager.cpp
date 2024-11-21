#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

#include "EnemyManager.h"
#include "EffectManager.h"

GameManager::GameManager(void)
	:map(nullptr), player(nullptr), gameOver(nullptr), timeFlew(0), pause(false), respawn(true), doCollision(true)
{
	m_GameStart = true;
}

GameManager::~GameManager(void)
{
	Delete();
}

void GameManager::Init()
{
	map = new Map();
	player = new Player();
	enemyManager = new EnemyManager();
	effectManager = new EffectManager();
	gameOver = new Sprite2();

	map->Init("./resource/Img/Game/map/map_bg.png");
	player->Init();

	enemyManager->Init();
	effectManager->Init();
	
	srand(time(NULL));

	int randomX = 100;
	int randomY = 100;
	int randDirX = 1;
	int randDirY = 1;

	float scale = 1;

	gameOver->Create("./resource/Img/lobby/introBG.png", false, D3DCOLOR_XRGB(0, 0, 0));
	
	Time::GetInstance().InitTime();
}

void GameManager::Update()
{
	Time::GetInstance().UpdateTime(1);
	if (!pause)
	{
		//if(게임 종료시) {g_Mng.n_Chap = OVER; Camera::GetInstance().SetCamX(0); Camera::GetInstance().SetCamY(0);}
		map->Update();

		if (player->GetState() != CS_DEAD)
		{
			timeFlew += TIME;

			player->Update();
			//이동 처리
			D3DXVECTOR2 velocity = player->GetVelocity();
			player->Move(velocity.x, velocity.y);

			if (respawn)
				enemyManager->Spawn();

			D3DXVECTOR2 playerPos = player->GetPos();
			enemyManager->Sort(playerPos.x, playerPos.y);
			enemyManager->Update();

			if(doCollision)
				enemyManager->CheckCollision(player);

			effectManager->Update();
		}
		else
		{
			//Game Over 상황
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				g_Mng.n_Chap = OVER;
			}
		}
	}
}
void GameManager::Draw()
{
	D3DXVECTOR2 playerPos = player->GetPos();
	

	map->Draw();
	enemyManager->Draw();
	player->Draw();
	effectManager->Draw();


	if (player->GetState() != CS_DEAD)
	{
		if (IsPause())
		{
			dv_font.DrawString("ON PAUSE", 420, 300, 0xffff0000);
		}
		else
		{
			dv_font.DrawString("WASD 혹은 방향키 - 이동", 20, 550, 0xffffffff);
			dv_font.DrawString("SPACEBAR - (임시)공격", 20, 600, 0xffffffff);
		}
		int minute = timeFlew / 60;
		int second = ((int)timeFlew) % 60;
		
		char timeFlew[16] = {};
		sprintf_s(timeFlew, "%d:%02d", minute, second);
		int len = strlen(timeFlew) / 2;

		dv_font.DrawString(timeFlew, (SCREEN_WITH / 2) - (len*12), 100);

		char debug[32] = {};
		sprintf_s(debug, "충돌 처리: %s", doCollision ? "TRUE" : "FALSE");
		dv_font.DrawString(debug, 15, 15);
		sprintf_s(debug, "적 생성중: %s", respawn ? "TRUE" : "FALSE");
		dv_font.DrawString(debug, 15, 45);
	}
	else
	{
		gameOver->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, 0x66ffffff, false);
		dv_font.DrawString("GAME OVER", 420, 300, 25, 12, 500, 0xffff0000);
	}
}

void GameManager::Delete()
{
	//	sound.g_pSoundManager->drr  
	SAFE_DELETE(map);

	SAFE_DELETE(player);
	SAFE_DELETE(enemyManager);
	SAFE_DELETE(effectManager);

	SAFE_DELETE(gameOver);
}

void GameManager::RegisterEffect(Effect* effect)
{
	effectManager->RegisterEffect(effect);
}

void GameManager::GameReset(void)  // 여기는 게임상 첨에 한번만  초기화되는 부분만 넣어줌.
{

}
