#pragma once

#include "Include.h"
#include "Singleton.h"

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
	//�÷��̾�
	Player* player;
	//�� ��ü ����
	EnemyManager* enemyManager;
	//�⺻ ����Ʈ ����
	EffectManager* effectManager;
	//���� ���� ��ũ��
	Sprite2* gameOver;
private:
	void GameReset(void);
	void Init();
	void Update();
	void Draw();
	void Delete();
public:
	bool m_GameStart;
public:
	void Pause() { pause = true; }
	void Resume() { pause = false; }
	bool IsPause() { return pause; }
	bool ToggleCollision() { return (doCollision = !doCollision); }
	bool ToggleSpawn() { return (respawn = !respawn); }
public:
	void RegisterEffect(Effect* effect);
	const Player* GetPlayer() const { return player; }
	bool showDebug;
};