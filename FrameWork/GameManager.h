#pragma once

#include "Include.h"
#include "Singleton.h"

class Effect;

class Enemy;
class PlayerManager;
class EnemyManager;
class EffectManager;

struct WeaponData;
class GameState;

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
	friend class Game;
private:
	GameManager(void);
	~GameManager(void);
private:
	//���� ���� ������ 
	bool pause;	    //�Ͻ����� ����
	bool respawn;	//�� ������ ����
	bool doCollision;//�浹 ó�� ����
	float timeFlew; //���� ������ ����� �ð�
	
	//���� ��ũ�� ��
	Map* map;
	//�÷��̾� ����
	PlayerManager* playerManager;
	//Player* player;
	//�� ��ü ����
	EnemyManager* enemyManager;
	//�⺻ ����Ʈ ����
	EffectManager* effectManager;
	//UI ���۳�Ʈ
	Sprite2* skull;
	Sprite2* coin;
	Sprite2* squareSprite;

	//Temp
	GameState* currentState;
	//Temp
	Enemy* temp_Boss;

	//Temp - Level
	int currentLevel;

	int currentXP;
	int nextLevelXP;
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

	void EarnXP(int xp);

	void TempEarnWeapon(WeaponData* data);
	void TempExitState();
public:
	void RegisterEffect(Effect* effect);
	bool showDebug;
};