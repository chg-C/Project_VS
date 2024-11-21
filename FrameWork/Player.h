#pragma once
#include "Include.h"
#include "Character.h"
#include "Projectile.h"

#include <vector>
using std::vector;


class Player : public Character
{
	bool damaging;
	float invTime;

	float speed;

	bool moving;

	int dir = 1;

	SpriteAnimation* attackEffectTemplate;

	DWORD playerColor;
	int alpha = 0xff;

	float attackCooldown;

	Sprite2* squareSprite;
public :
	Player();
	~Player();

	std::list<Projectile*> projectiles;

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	void DrawHealthBar();

	virtual void Move(float x, float y);
	virtual void Damage(float dmg);
};