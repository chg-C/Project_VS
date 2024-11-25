#include "Include.h"
#include "MovingProjectile.h"

void MovingProjectile::Update()
{
	Projectile::Update();

	x += direction.x * speed;
	y += direction.y * speed;
	range -= direction.x * speed;
	range -= direction.y * speed;

	if (range <= 0)
		finished = true;	
}

void MovingProjectile::Collide(Enemy* enemy)
{
	lifetime -= 1;
	if (lifetime <= 0)
		finished = true;

	Projectile::Collide(enemy);
}
