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