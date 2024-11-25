#pragma once
#include "Singleton.h"

typedef struct {
    int enemyID;           // �� ���� ID
    int animatorID;        // �ִϸ����� ID
    int maxHealth;         // �ִ� ü��
    float moveSpeed;       // �̵� �ӵ�
    int attackPower;       // ���ݷ�
} EnemyData;

// �÷��̾� ������ ����ü
typedef struct {
    int playerID;          // �÷��̾� ĳ���� ���� ID
    int animatorID;        // �ִϸ����� ID
    int maxHealth;         // �ִ� ü��
    float moveSpeed;       // �̵� �ӵ�
    int defense;           // ����
    int attackPower;       // ���ݷ�
    float attackSpeed;     // ���� �ӵ�
} PlayerData;

typedef struct {
    int projectileID;      //����ü ���� ID
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