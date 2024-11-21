#include "Include.h"
#include "Projectile.h"

Projectile::Projectile(SpriteAnimation* sprites, float x, float y, int dir, float scale)
	: SpriteEffect(sprites, x, y, scale), dir(dir), damage(8)
{
	this->sprites = new SpriteAnimation(*sprites);
}

Projectile::~Projectile()
{
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
	for (auto& iter : collidedList)
	{
		if (iter.enemy == enemy)
			return false;
	}
	return true;
}

float Projectile::GetDamage()
{
	return damage;
}
