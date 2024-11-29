#include "Include.h"
#include "LoopProjectile.h"

LoopProjectile::LoopProjectile(SpriteAnimation* sprites, float damage, float cooldown, float scale, const Character* owner)
	: Projectile(sprites, 0, 0, 1, damage, cooldown, scale), owner(owner)
{
}

LoopProjectile::~LoopProjectile()
{
}

void LoopProjectile::Update()
{
	D3DXVECTOR2 vp = owner->GetPos();
	x = vp.x;
	y = vp.y;

	sprites->Update();
	width = sprites->GetCurrentSpriteData()->sprite->imagesinfo.Width * scale;
	height = sprites->GetCurrentSpriteData()->sprite->imagesinfo.Height * scale;

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
//
//void LoopProjectile::Draw()
//{
//}
