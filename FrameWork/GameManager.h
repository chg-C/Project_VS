#pragma once

#include "Include.h"
#include "Singleton.h"

#include "Enemy.h"

#include <list>
using std::list;

struct SysTem
{
	int m_Save1;
	int m_Save2;

};

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;
public:
	GameManager(void);
	~GameManager(void);

	FILE *fp;
	SysTem m_SysTem;

	bool m_Pause;
	int m_GameSpeed;
	
	DWORD GameTime;
	bool m_GameStart;

	bool m_Collision;

	bool Respawn;


	Map* map;
	Player* player;
	list<Enemy*> enemies;

	D3DXVECTOR2 CheckEnemyCollision(Enemy* enemy);
	bool IsColliding(RECT& rectA, RECT& rectB);


	void GameReset(void);
	void Init();
	void Update();
	void Draw();
	void Save();
	void Delete();
};