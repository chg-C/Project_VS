#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"


GameManager::GameManager(void)
	:map(nullptr), playerManager(nullptr), gameOver(nullptr), timeFlew(0), pause(false), respawn(true), doCollision(true)
{
	m_GameStart = true;
	showDebug = true;
}

GameManager::~GameManager(void)
{
	Delete();
}

void GameManager::Init()
{
	map = new Map();
	//player = new Player(data);
	playerManager = new PlayerManager();
	enemyManager = new EnemyManager();
	effectManager = new EffectManager();
	gameOver = new Sprite2();

	map->Init("./resource/Img/Game/map/map_bg.png");
	
	PlayerData* data = ResourceManager::GetInstance().GetPlayerData(ID_PLAYER_ANTONIO);
	playerManager->Init(data);
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
	Option::GetInstance().Init();

	timeFlew = 0;
	pause = false;
}

void GameManager::Update()
{
	Time::GetInstance().UpdateTime(1);
	if (!pause)
	{
		//if(게임 종료시) {g_Mng.n_Chap = OVER; Camera::GetInstance().SetCamX(0); Camera::GetInstance().SetCamY(0);}
		map->Update();

		if (playerManager->IsPlaying())
		{
			timeFlew += TIME;

			playerManager->Update();

			if (respawn)
				enemyManager->Spawn();

			D3DXVECTOR2 playerPos = playerManager->GetPlayerPos();
			enemyManager->Sort(playerPos.x, playerPos.y);
			enemyManager->Update();

			if(doCollision)
				enemyManager->CheckCollision(playerManager);

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
	map->Draw();
	enemyManager->Draw();
	playerManager->Draw();
	effectManager->Draw();


	if (playerManager->IsPlaying())
	{
		if (IsPause())
		{
			dv_font.DrawString("ON PAUSE", 420, 300, 0xffff0000);
		}

		int minute = timeFlew / 60;
		int second = ((int)timeFlew) % 60;
		
		char timeFlew[16] = {};
		sprintf_s(timeFlew, "%d:%02d", minute, second);
		int len = strlen(timeFlew) / 2;
		dv_font.DrawString(timeFlew, (SCREEN_WITH / 2) - (len * 12), 100);
		//

		if (showDebug)
		{
			//
			char debug[64] = {};
			sprintf_s(debug, "충돌 처리(1): %s", doCollision ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 150);
			sprintf_s(debug, "적 생성중(2): %s", respawn ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 165);
			sprintf_s(debug, "대미지 숫자 출력(3): %s", Option::GetInstance().WillDamageEffect() ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 180);

			sprintf_s(debug, "현재 캐릭터(4): %s", playerManager->GetPlayerName());
			dv_font.DrawString(debug, 15, 300);
		}
		dv_font.DrawString("WASD 혹은 방향키 - 이동", 15, 550, 0xffffffff);
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

	SAFE_DELETE(playerManager);
	SAFE_DELETE(enemyManager);
	SAFE_DELETE(effectManager);

	SAFE_DELETE(gameOver);
}

Enemy* GameManager::FindClosestEnemy()
{
	if (enemyManager->enemies.size() <= 0)
		return nullptr;
	else
		return (*enemyManager->enemies.begin());
}

void GameManager::RegisterEffect(Effect* effect)
{
	effectManager->RegisterEffect(effect);
}

/// <summary>
/// 게임 초기화
/// </summary>
void GameManager::GameReset()
{
	Delete();
	Init();
}
