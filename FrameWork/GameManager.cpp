#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Score.h"

#include "GameStateInclude.h"


GameManager::GameManager(void)
	:map(nullptr), playerManager(nullptr), enemyManager(nullptr), effectManager(nullptr), timeFlew(0), pause(false), respawn(true), doCollision(true),
	currentXP(0), nextLevelXP(5), currentLevel(1), onLevelUp(false), currentState(nullptr)
{
	m_GameStart = true;
	showDebug = true;
}

GameManager::~GameManager(void)
{
	Delete();
}
void GameManager::Delete()
{
	//	sound.g_pSoundManager->drr  
	SAFE_DELETE(map);

	SAFE_DELETE(playerManager);
	SAFE_DELETE(enemyManager);
	SAFE_DELETE(effectManager);

	SAFE_DELETE(currentState);

	SAFE_DELETE(skull);
	SAFE_DELETE(coin);
	SAFE_DELETE(squareSprite);


	temp_Boss = nullptr;
}

void GameManager::Init()
{
	map = new Map();
	//player = new Player(data);
	playerManager = new PlayerManager();
	enemyManager = new EnemyManager();
	effectManager = new EffectManager();

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

	Time::GetInstance().InitTime();
	Option::GetInstance().Init();
	Score::GetInstance().Reset();

	timeFlew = 0;
	pause = false;

	skull = new Sprite2();
	skull->Create("./resource/Img/Etc/SkullToken.png", false);
	coin = new Sprite2();
	coin->Create("./resource/Img/Etc/coin-spin-gold_01.png", false); 
	squareSprite = new Sprite2();
	squareSprite->Create("./resource/Img/Etc/Square.png", false);

	temp_Boss = nullptr;
	gameClearing = gameClear = false;

	currentXP = 0;
	nextLevelXP = 5;
	currentLevel = 1;

	onLevelUp = false;

	currentState = nullptr;
}

void GameManager::Update()
{
	Time::GetInstance().UpdateTime(1);
	
	if (currentState != nullptr)
	{
		currentState->Update();
	}
	else
	{
		map->Update();

		if (KeyDown('0'))
		{
			timeFlew = 900;
		}
		if (playerManager->IsPlaying())
		{
			timeFlew += TIME;
			Score::GetInstance().SetTimeFlew(timeFlew);

			if (temp_Boss != nullptr)
			{
				if (!temp_Boss->IsAlive())
				{
					currentState = new GameState_Clear(temp_Boss);
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
			if (playerManager->GetPlayer()->GetState() == CS_DEAD)
			{
				currentState = new GameState_GameOver();
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

	//XP
	squareSprite->DrawStretch(0, 0, SCREEN_WITH, 30, 0xff111111, false);
	float p = (currentXP / (float)nextLevelXP);
	if (p > 1)
		p = 1;
	float xpGauge = SCREEN_WITH * p;
	squareSprite->DrawStretch(0, 0, xpGauge, 30, 0xff1111ff, false);

	char level[24] = "";
	sprintf_s(level, "LV %d", currentLevel);
	int len = strlen(level);
	dv_font.DrawString(level, SCREEN_WITH - 50 - (12 * len), 10, 16, 12);

	if (currentState != nullptr)
	{
		currentState->Draw();
	}
	else
	{
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
			sprintf_s(debug, "충돌 처리(1): %s", doCollision ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 150);
			sprintf_s(debug, "적 생성중(2): %s", respawn ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 165);
			sprintf_s(debug, "대미지 숫자 출력(3): %s", Option::GetInstance().WillDamageEffect() ? "TRUE" : "FALSE");
			dv_font.DrawString(debug, 15, 180);

			sprintf_s(debug, "현재 캐릭터(4): %s", playerManager->GetPlayerName());
			dv_font.DrawString(debug, 15, 300);

			dv_font.DrawString("채찍 아이템 획득(5)", 15, 350);
			dv_font.DrawString("마늘 아이템 획득(6)", 15, 380);
			dv_font.DrawString("지팡이 아이템 획득(7)", 15, 400);

			dv_font.DrawString("보스 생성하기(0)", 15, 450);
		}

		dv_font.DrawString("F1 - 디버그 키 표시하기", 15, 500);
		dv_font.DrawString("WASD 혹은 방향키 - 이동", 15, 550, 16, 8, 500, 0xffffffff);
	}
}

Enemy* GameManager::FindClosestEnemy()
{
	if (enemyManager->GetEnemyCount() <= 0)
		return nullptr;
	else
		return enemyManager->FindFirstEnemy();
}

void GameManager::EarnXP(int xp)
{
	currentXP += xp;

	if (currentXP >= nextLevelXP)
	{
		++currentLevel;

		currentXP = 0;
		nextLevelXP += currentLevel * 15;

		onLevelUp = true;
	}
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