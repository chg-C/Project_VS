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

typedef struct {
    int projectileID;      //투사체 고유 ID
    int animationID;       //
} ProjectileData;

struct sqlite3;

enum PlayerAnimatorID { ID_PLAYER_BEGIN = 1000, ID_PLAYER_ANTONIO = 1001 };
enum EnemyAnimatorID { ID_ENEMY_BEGIN = 10000, ID_ENEMY_BAT, ID_ENEMY_MUDMAN };
enum EffectAnimationIDs { ID_EFFECT_BEGIN = 100000, ID_EFFECT_WHIP };

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
private:
	ResourceManager();
	virtual ~ResourceManager();
private:
    sqlite3* database;
public:
	void InitResources();
    //
    AnimationClip* LoadClip(int id);
    SpriteAnimation* LoadAnimation(int id);
    SpriteAnimator* LoadAnimator(int id);

    PlayerData* LoadPlayerData(int id);
    EnemyData* LoadEnemyData(int id);

    //
    AnimationClip* GetClip(int id);
	SpriteAnimation* GetAnimation(int id);
	SpriteAnimator* GetAnimator(int id);
    
    PlayerData* GetPlayerData(int id);
    EnemyData* GetEnemyData(int id);
};