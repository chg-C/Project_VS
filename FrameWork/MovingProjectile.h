#pragma once

class Enemy;
class Projectile;

class MovingProjectile : public Projectile
{
public:
	MovingProjectile(SpriteAnimation* sprites, float x, float y, D3DXVECTOR2 dir, float damage, float range, float speed, int lifetime, float scale = 1);
	~MovingProjectile();
private:
	float lifetime;
	float range;
	float speed;

	D3DXVECTOR2 direction;
public:
	virtual void Update();
	virtual void Draw();
	virtual void Collide(Enemy* enemy);
};

