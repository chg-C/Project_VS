#pragma once
#include "Singleton.h"

typedef struct {
    int enemyID;           // �� ���� ID
    int animatorID;        // �ִϸ����� ID
    int maxHealth;         // �ִ� ü��
    float moveSpeed;       // �̵� �ӵ�
    float attackPower;       // ���ݷ�
} EnemyData;

// �÷��̾� ������ ����ü
typedef struct {
    int playerID;          // �÷��̾� ĳ���� ���� ID
    char playerName[64];   // �÷��̾� ĳ���� �̸�
    int animatorID;        // �ִϸ����� ID
    int maxHealth;         // �ִ� ü��
    float moveSpeed;       // �̵� �ӵ�
    int defense;           // ����
    float attackPower;       // ���ݷ�
    float attackSpeed;     // ���� �ӵ�,

    int defaultWeaponID;   //�⺻ ���� ID
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
/// �̵��ϴ� ���� ������
/// = �ӵ�, ��Ÿ� �ʿ�
/// </summary>
struct WeaponStatusData_Move : public WeaponStatusData
{
    float speed;
    float range;
    int lifetime;
};

/// <summary>
/// ������ ����ü ����
/// DEFAULT = �⺻, ä�� �� 1ȸ �÷��� �� ����.
/// MOVEDIR = Ư�� �������� �̵�, ���� �Ÿ� ���� Ȥ�� ���� �浹 ȸ���� ���� ���ؿ� �����ϸ� ����
/// FOLLOW = Ư�� ĳ���͸� ���� �̵�. ���� �Ÿ� �̻� �̵��ϰų� ���� �浹�ϸ� ����
/// LOOP = ���ӽð� ����. ���� �� ���� ���ӵǴ� ���⸸ ���
/// AREA = ���� �ð� �� ����.
/// </summary>
enum WeaponType {WEAPON_DEFAULT, WEAPON_MOVEDIR, WEAPON_FOLLOW, WEAPON_LOOP, WEAPON_AREA};

struct WeaponData {
    int weaponID;        //������ ���� ID
    Sprite2* weaponIcon; //���� Icon
    WeaponType type;     //������ �۵� Ÿ��
    int projectileID;    //���Ⱑ ����� ����ü�� ID
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
/// ����ü �ؽ�ó
/// </summary>
struct ProjectileData {
    int projectileID;      //����ü ���� ID
    int animationID;       //����ü�� ��������Ʈ �ִϸ��̼� ID
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
    //��������Ʈ �ִϸ��̼�
    AnimationClip* LoadClip(int id);
    SpriteAnimation* LoadAnimation(int id);
    SpriteAnimator* LoadAnimator(int id);

    AnimationClip* GetClip(int id);
    SpriteAnimation* GetAnimation(int id);
    SpriteAnimator* GetAnimator(int id);

    //���� ������
    PlayerData* LoadPlayerData(int id);
    EnemyData* LoadEnemyData(int id);
    ProjectileData* LoadProjectileData(int id);
    WeaponData* LoadWeaponData(int id);

    PlayerData* GetPlayerData(int id);
    EnemyData* GetEnemyData(int id);
    ProjectileData* GetProjectileData(int id);
    WeaponData* GetWeaponData(int id);
};