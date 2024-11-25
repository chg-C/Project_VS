#pragma once

class Enemy;
class Projectile;

class MovingProjectile : public Projectile
{
public:
	MovingProjectile();
	~MovingProjectile();
private:
	float lifetime;
	float range;
	float speed;

	D3DXVECTOR2 direction;
public:
	virtual void Update();
	virtual void Collide(Enemy* enemy);
};

