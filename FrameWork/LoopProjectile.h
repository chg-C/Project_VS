#pragma once

class Character;
class Enemy;
class Projectile;

class LoopProjectile : public Projectile
{
private:
	const Character* owner;
public:
	LoopProjectile(SpriteAnimation* sprites, float damage, float cooldown, float scale, const Character* owner);
	~LoopProjectile();
public:
	//virtual void Init();
	virtual void Update();
	//virtual void Draw();
};