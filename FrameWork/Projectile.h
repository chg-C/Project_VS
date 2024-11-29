#pragma once
#include "SpriteEffect.h"
#include "Enemy.h"

struct Collided
{
	Collided(float time, Enemy* enemy)
		:	time(time), enemy(enemy)
	{

	}

	float time;
	const Enemy* enemy;
};

class Projectile : public SpriteEffect
{
public:
	Projectile(SpriteAnimation* sprites, float x, float y, int dir, float damage, float cooldown, float scale=1);
	virtual ~Projectile();
protected:
	int dir;
	std::list<Collided> collidedList;

	float damage;
	float cooldown;
public:
	RECT GetCollider(float mp = 1) {
		return RECT{
		  (long)(x - (width * scale / 2)),
		  (long)(y - (height * scale / 2 )),
		  (long)(x + (width * scale / 2)),
		  (long)(y + (height * scale / 2)),
		};
	}
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	bool CanCollide(Enemy* enemy);
	virtual void Collide(Enemy* enemy);

	float GetDamage();
};