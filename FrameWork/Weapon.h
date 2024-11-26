#pragma once
#include "Item.h"

struct WeaponData;

class Projectile;
class Player;

class Weapon : public Item
{
private:
	std::list<Projectile*> projectiles;
	const WeaponData* data;
	const Player* player;

	int projectileCount;
	float delay;

	bool generating;
public:
	Weapon(const WeaponData* data, const Player* player);
	virtual ~Weapon();
public:
	virtual void Init();
	virtual void Update(float speed = 1);
	virtual void Draw();
public:
	std::list<Projectile*>& GetProjectiles();
	Sprite2* GetIcon();
	void SetPlayer(const Player* player);
};

