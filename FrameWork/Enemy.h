#pragma once

#include "Character.h"
#include "Sprite2.h"
#include "ResourceManager.h"

#include <vector>
using std::vector;

class Enemy : public Character
{
private:
	bool damaging;
	float damageDelay;

	//Status
	float moveSpeed;
	float attackDamage;
	
	// Rendering
	int spriteIdx;
public:
	Enemy(EnemyData* data, float x, float y, float scale = 1);
	~Enemy();
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Move(float x, float y);

	virtual void Damage(float dmg);
public:
	float GetDamage() { return attackDamage; }
};

