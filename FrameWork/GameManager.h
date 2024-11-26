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
	//���� ���� ��ũ��
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