#include "Include.h"
#include "MovingProjectile.h"

MovingProjectile::MovingProjectile(SpriteAnimation* sprites, float x, float y, D3DXVECTOR2 dir, float damage, float range, float speed, int lifetime, float scale)
	:Projectile(sprites, x, y, 1, damage, 9, scale), range(range), speed(speed), lifetime(lifetime)
{
	D3DXVec2Normalize(&direction, &dir);
}

MovingProjectile::~MovingProjectile()
{
}

void MovingProjectile::Update()
{
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

	x += direction.x * speed;
	y += direction.y * speed;
	range -= abs(direction.x * speed);
	range -= abs(direction.y * speed);

	if (range <= 0)
		finished = true;
}

void MovingProjectile::Draw()
{
	if (!finished)
	{
		sprites->GetCurrentSpriteData()->sprite->RenderStretch(x, y, width, height, scale * dir, scale, 
			sprites->GetCurrentSpriteData()->color, true, 0);
	}
}

void MovingProjectile::Collide(Enemy* enemy)
{
	lifetime -= 1;
	if (lifetime <= 0)
		finished = true;

	Projectile::Collide(enemy);
}
