#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Score.h"


GameManager::GameManager(void)
	:map(nullptr), playerManager(nullptr), enemyManager(nullptr), effectManager(nullptr), gameOver(nullptr), timeFlew(0), pause(false), respawn(true), doCollision(true)
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
	Score::GetInstance().Reset();

	timeFlew = 0;
	pause = false;

	skull = new Sprite2();
	skull->Create("./resource/Img/Etc/SkullToken.png", false);
	coin = new Sprite2();
	coin->Create("./resource/Img/Etc/coin-spin-gold_01.png", false);

	temp_Boss = nullptr;
	gameClearing = gameClear = false;
}

void GameManager::Update()
{
	Time::GetInstance().UpdateTime(1);
	if (gameClearing)
	{
		if (temp_Boss != nullptr)
			temp_Boss->Update();

		if (temp_Boss->GetState() == CS_DEAD)
		{
			gameClear = true;
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			{
				key.KeyTime = GetTickCount64();
				g_Mng.n_Chap = OVER;
			}
		}
	}
	else
	{
		if (!pause)
		{
			//if(���� �����) {g_Mng.n_Chap = OVER; Camera::GetInstance().SetCamX(0); Camera::GetInstance().SetCamY(0);}
			map->Update();

			if (KeyDown('0'))
			{
				timeFlew = 900;
			}
			if (playerManager->IsPlaying())
			{
				timeFlew += TIME;

				if (temp_Boss != nullptr)
				{
					if (!temp_Boss->IsAlive())
					{
						gameClearing = true;
					}
				}
				else
				{
					if (timeFlew >= 900)
					{
						temp_Boss = enemyManager->Temp_SpawnBoss();
					}
				}

				playerManager->Update();

				if (respawn)
					enemyManager->Spawn();

				D3DXVECTOR2 playerPos = playerManager->GetPlayerPos();
				enemyManager->Sort(playerPos.x, playerPos.y);
				enemyManager->Update();

				if (doCollision)
					enemyManager->CheckCollision(playerManager);

				effectManager->Update();
			}
			else
			{
				//Game Over ��Ȳ
				if (GetAsyncKeyState(VK_RETURN) & 0x8000)
				{
					key.KeyTime = GetTickCount64();
					g_Mng.n_Chap = OVER;
				}
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

	if (gameClear)
	{
		gameOver->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, 0x66ffffff, false);
		dv_font.DrawString("GAME CLEAR!", 420, 300, 25, 12, 500, 0xffffffff);
	}
	else if (playerManager->IsPlaying())
	{
		if (IsPause())
		{
			dv_font.DrawString("ON PAUSE", 420, 300, 0xffff0000);
		}

		int minute = timeFlew / 60;
		int second = ((int)timeFlew) % 60;
		
		char data[16] = {};
		sprintf_s(data, "%d:%02d", minute, second);
		int len = strlen(data) / 2;
		dv_font.DrawString(data, (SCREEN_WITH / 2) - (len * 12), 50);
		//

		sprintf_s(data, "%d", Score::GetInstance().GetKillCount());
		len = strlen(data) / 2;
		dv_font.DrawString(data, (SCREEN_WITH - 180) - (len * 12), 50);
		skull->DrawStretch(SCREEN_WITH - 160, 48, 20, 20, 0xffffffff, false);

		sprintf_s(data, "%d", Score::GetInstance().GetEarnedGold());
		len = strlen(data) / 2;
		dv_font.DrawString(data, (SCREEN_WITH - 80) - (len * 12), 50);
		coin->DrawStretch(SCREEN_WITH - 60, 48, 20, 20, 0xffffffff, false);

		if (showDebug)
		{
			//
			char debug[64] = {};
			sprintf_s(debug, "�浹 ó��(1): %s", doCollision ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 150);
			sprintf_s(debug, "�� ������(2): %s", respawn ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 165);
			sprintf_s(debug, "����� ���� ���(3): %s", Option::GetInstance().WillDamageEffect() ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 180);

			sprintf_s(debug, "���� ĳ����(4): %s", playerManager->GetPlayerName());
			dv_font.DrawString(debug, 15, 300);

			dv_font.DrawString("ä�� ������ ȹ��(5)", 15, 350);
			dv_font.DrawString("���� ������ ȹ��(6)", 15, 365);
			dv_font.DrawString("������ ������ ȹ��(7)", 15, 380);

			dv_font.DrawString("���� �����ϱ�(0)", 15, 450);
		}

		dv_font.DrawString("F1 - ����� Ű ǥ���ϱ�", 15, 500);
		dv_font.DrawString("WASD Ȥ�� ����Ű - �̵�", 15, 550, 0xffffffff);
	}
	else
	{
		gameOver->DrawStretch(0, 0, SCREEN_WITH, SCREEN_HEIGHT, 0x88ffffff, false);
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

	SAFE_DELETE(skull);
	SAFE_DELETE(coin);
	temp_Boss = nullptr;
}

Enemy* GameManager::FindClosestEnemy()
{
	if (enemyManager->GetEnemyCount() <= 0)
		return nullptr;
	else
		return enemyManager->FindFirstEnemy();
}

void GameManager::RegisterEffect(Effect* effect)
{
	effectManager->RegisterEffect(effect);
}

/// <summary>
/// ���� �ʱ�ȭ
/// </summary>
void GameManager::GameReset()
{
	Delete();
	Init();
}