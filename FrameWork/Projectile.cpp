#include "Include.h"
#include "Projectile.h"

Projectile::Projectile(SpriteAnimation* sprites, float x, float y, int dir, float damage, float cooldown, float scale)
	: SpriteEffect(sprites, x, y, scale), dir(dir), damage(damage), cooldown(cooldown)
{
	this->sprites = new SpriteAnimation(*sprites);
}

Projectile::~Projectile()
{
	collidedList.clear();
}

void Projectile::Init()
{
	SpriteEffect::Init();
}

void Projectile::Update()
{
	SpriteEffect::Update();

	for (auto& iter = collidedList.begin(); iter != collidedList.end();)
	{
		(*iter).time -= TIME;
		if ((*iter).time < 0)
		{
			iter = collidedList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Projectile::Draw()
{
	if (!finished)
		sprites->GetCurrentSpriteData()->sprite->RenderStretch(x, y, width, height, scale*dir, scale, sprites->GetCurrentSpriteData()->color);
}

bool Projectile::CanCollide(Enemy* enemy)
{
	if (!sprites->GetCurrentSpriteData()->hasCollision)
		return false;

	for (auto& iter : collidedList)
	{
		if (iter.enemy == enemy)
			return false;
	}
	return true;
}

void Projectile::Collide(Enemy* enemy)
{
	collidedList.push_back(Collided(cooldown, enemy));
}

float Projectile::GetDamage()
{
	return damage;
}
