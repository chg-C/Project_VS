#pragma once
#include "Singleton.h"

typedef struct {
    int enemyID;           // 적 고유 ID
    int animatorID;        // 애니메이터 ID
    int maxHealth;         // 최대 체력
    float moveSpeed;       // 이동 속도
    float attackPower;       // 공격력
} EnemyData;

// 플레이어 데이터 구조체
typedef struct {
    int playerID;          // 플레이어 캐릭터 고유 ID
    char playerName[64];   // 플레이어 캐릭터 이름
    int animatorID;        // 애니메이터 ID
    int maxHealth;         // 최대 체력
    float moveSpeed;       // 이동 속도
    int defense;           // 방어력
    float attackPower;       // 공격력
    float attackSpeed;     // 공격 속도,

    int defaultWeaponID;   //기본 무기 ID
} PlayerData;

struct WeaponStatusData {
    int statID;
    int baseWeaponID;
    int level;
    float damage;
    float delay;
    float scale;
    int projectileCount;
};
/// <summary>
/// 이동하는 무기 데이터
/// = 속도, 사거리 필요
/// </summary>
struct WeaponStatusData_Move : public WeaponStatusData
{
    float speed;
    float range;
    int lifetime;
};

/// <summary>
/// 무기의 투사체 종류
/// DEFAULT = 기본, 채찍 등 1회 플레이 후 삭제.
/// MOVEDIR = 특정 방향으로 이동, 일정 거리 도달 혹은 적과 충돌 회수가 일정 수준에 도달하면 삭제
/// FOLLOW = 특정 캐릭터를 향해 이동. 일정 거리 이상 이동하거나 적과 충돌하면 삭제
/// LOOP = 지속시간 없음. 마늘 등 무한 지속되는 무기만 사용
/// AREA = 일정 시간 후 삭제.
/// </summary>
enum WeaponType {WEAPON_DEFAULT, WEAPON_MOVEDIR, WEAPON_FOLLOW, WEAPON_LOOP, WEAPON_AREA};

struct WeaponData {
    int weaponID;        //무기의 고유 ID
    Sprite2* weaponIcon; //무기 Icon
    WeaponType type;     //무기의 작동 타입
    int projectileID;    //무기가 사용할 투사체의 ID
    int maxLevel;
    
    std::vector<WeaponStatusData*> stats;

    ~WeaponData()
    {
        for (auto& iter : stats)
        {
            delete iter;
            iter = nullptr;
        }
        stats.clear();
    }
};

/// <summary>
/// 투사체 텍스처
/// </summary>
struct ProjectileData {
    int projectileID;      //투사체 고유 ID
    int animationID;       //투사체의 스프라이트 애니메이션 ID
};

struct sqlite3;

enum PlayerAnimatorID { ID_PLAYER_BEGIN = 0, ID_PLAYER_ANTONIO, ID_PLAYER_MUDMAN, ID_PLAYER_BAT, ID_PLAYER_END };
enum EnemyAnimatorID { ID_ENEMY_BEGIN = 10000, ID_ENEMY_BAT, ID_ENEMY_MUDMAN, ID_ENEMY_MANTIS, ID_ENEMY_END };
enum EffectAnimationIDs { ID_EFFECT_BEGIN = 100000, ID_EFFECT_WHIP, ID_EFFECT_FIREBALL, ID_EFFECT_MISSILE, ID_EFFECT_CIRCLE, ID_EFFECT_THUNDER, ID_EFFECT_END };

enum WeaponIDs {ID_WEAPON_BEGIN = 1000, 
    ID_WEAPON_WHIP, ID_WEAPON_GARLIC, ID_WEAPON_MAGICWAND, ID_WEAPON_FIREWAND,
    ID_WEAPON_END};

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
    //스프라이트 애니메이션
    AnimationClip* LoadClip(int id);
    SpriteAnimation* LoadAnimation(int id);
    SpriteAnimator* LoadAnimator(int id);

    AnimationClip* GetClip(int id);
    SpriteAnimation* GetAnimation(int id);
    SpriteAnimator* GetAnimator(int id);

    //게임 데이터
    PlayerData* LoadPlayerData(int id);
    EnemyData* LoadEnemyData(int id);
    ProjectileData* LoadProjectileData(int id);
    WeaponData* LoadWeaponData(int id);

    PlayerData* GetPlayerData(int id);
    EnemyData* GetEnemyData(int id);
    ProjectileData* GetProjectileData(int id);
    WeaponData* GetWeaponData(int id);
};