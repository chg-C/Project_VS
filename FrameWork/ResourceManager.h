#pragma once
#include "Singleton.h"

typedef struct {
    int enemyID;           // 적 고유 ID
    int animatorID;        // 애니메이터 ID
    int maxHealth;         // 최대 체력
    float moveSpeed;       // 이동 속도
    int attackPower;       // 공격력
} EnemyData;

// 플레이어 데이터 구조체
typedef struct {
    int playerID;          // 플레이어 캐릭터 고유 ID
    int animatorID;        // 애니메이터 ID
    int maxHealth;         // 최대 체력
    float moveSpeed;       // 이동 속도
    int defense;           // 방어력
    int attackPower;       // 공격력
    float attackSpeed;     // 공격 속도
} PlayerData;

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
private:
	ResourceManager();
	virtual ~ResourceManager();
public:
	void InitResources();

	SpriteAnimation* GetAnimation(int id);
	SpriteAnimator* GetAnimator(int id);
    
    PlayerData* GetPlayerData(int id);
    EnemyData* GetEnemyData(int id);
};