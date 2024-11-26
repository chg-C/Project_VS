#pragma once

#include "Include.h"
#include "Singleton.h"

class Effect;

class Enemy;
class PlayerManager;
class EnemyManager;
class EffectManager;

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
	friend class Game;
private:
	GameManager(void);
	~GameManager(void);
private:
	//게임 상태 변수들 
	bool pause;	    //일시정지 상태
	bool respawn;	//적 리스폰 여부
	bool doCollision;//충돌 처리 여부
	float timeFlew; //게임 시작후 경과한 시간
	

	//무한 스크롤 맵
	Map* map;
	//플레이어 관리
	PlayerManager* playerManager;
	//Player* player;
	//적 객체 관리
	EnemyManager* enemyManager;
	//기본 이펙트 관리
	EffectManager* effectManager;
	//게임 오버 스크린
	Sprite2* gameOver;
private:
	void Init();
	void Update();
	void Draw();
	void Delete();
public:
	bool m_GameStart;
public:
	void GameReset(void);
	void Pause() { pause = true; }
	void Resume() { pause = false; }
	bool IsPause() { return pause; }
	bool ToggleCollision() { return (doCollision = !doCollision); }
	bool ToggleSpawn() { return (respawn = !respawn); }
	Enemy* FindClosestEnemy();
public:
	void RegisterEffect(Effect* effect);
	bool showDebug;
};