#pragma once

#include <list>
using std::list;

class Enemy;
class PlayerManager;

struct EnemySpawnPoint
{
	float x, y;

	float cooldown;
	int cdRandomRange;

	float cooldownRemain;
	

	Enemy* enemyTemplate;
};

class EnemyManager
{
public:
	~EnemyManager();
private:
	vector<EnemySpawnPoint> spawnPoints;
	list<Enemy*> enemies;

	bool flagA;
public:
	void Init();
	void Update();
	void Draw();

	void Spawn();

	Enemy* Temp_SpawnBoss();

	Enemy* SpawnSpecficEnemy(float x, float y, EnemyData* data);
	void Sort(float x, float y);
	
	void CheckCollision(PlayerManager* playerManager);

	bool IsColliding(RECT& rectA, RECT& rectB) {
		return (rectA.left < rectB.right && rectB.left < rectA.right && rectA.top < rectB.bottom && rectB.top < rectA.bottom);
	}
	D3DXVECTOR2 CheckEnemyCollision(Player* player, Enemy* enemy);

	int GetEnemyCount() const { return enemies.size(); }
	Enemy* FindFirstEnemy() { return (*enemies.begin()); }
};