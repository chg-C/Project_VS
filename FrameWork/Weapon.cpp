#include "Include.h"
#include "Projectile.h"
#include "MovingProjectile.h"
#include "LoopProjectile.h"
#include "Weapon.h"


Weapon::Weapon(const WeaponData* data, const Player* player)
	: data(data), player(player), generating(false), projectileCount(0), delay(1)
{
	
}

Weapon::~Weapon()
{
	for (auto& iter : projectiles)
	{
		SAFE_DELETE(iter);
	}
	projectiles.clear();
}

void Weapon::Init()
{
	delay = data->delay;

	if (data->type == WEAPON_LOOP)
	{
		Projectile* p = new LoopProjectile(ResourceManager::GetInstance().GetAnimation(data->projectileID),
			data->damage, data->delay, 1.5f, player);
		projectiles.push_back(p);
	}
}

void Weapon::Update(float speed)
{
	if (data->type != WEAPON_LOOP)
	{
		if (generating)
		{
			delay -= TIME;

			if (delay <= 0)
			{
				if (data->type == WEAPON_DEFAULT)
				{
					int tempDir = 1;
					if (projectileCount % 2 == 1)
						tempDir = -1;

					Projectile* proj = new Projectile(ResourceManager::GetInstance().GetAnimation(data->projectileID),
						player->GetPos().x + (80 * player->GetDirection() * tempDir), player->GetPos().y,
						player->GetDirection() * tempDir, data->damage, 3.0f, 0.5f);//pos.x + (100 * dir), pos.y, dir, 0.5f);
					proj->Init();
					projectiles.push_back(proj);
					//Projectile* projectile = new Projectile()

					projectileCount++;

					if (projectileCount >= data->projectileCount)
					{
						delay = data->delay;
						generating = false;
					}
					else
					{
						delay = 0.1f;
					}
				}
				else if (data->type == WEAPON_MOVEDIR)
				{
					Enemy* enemy = GameManager::GetInstance().FindClosestEnemy();
					if (enemy != nullptr)
					{
						D3DXVECTOR2 dir = enemy->GetPos() - player->GetPos();
						if (D3DXVec2Length(&dir) <= ((WeaponData_Move*)data)->range)
						{

							Projectile* proj = new MovingProjectile(ResourceManager::GetInstance().GetAnimation(data->projectileID),
								player->GetPos().x, player->GetPos().y, dir, data->damage,
								((WeaponData_Move*)data)->range, ((WeaponData_Move*)data)->speed, ((WeaponData_Move*)data)->lifetime);
							proj->Init();
							projectiles.push_back(proj);

							projectileCount++;

							if (projectileCount >= data->projectileCount)
							{
								delay = data->delay;
								generating = false;
							}
							else
							{
								delay = 0.1f;
							}
						}
					}
				}
			}
		}
		else
		{
			float time = TIME * speed;

			delay -= time;
			projectileCount = 0;// data->projectileCount;
			if (delay <= 0)
			{
				delay = 0;
				generating = true;
			}
		}
	}

	for (auto& iter = projectiles.begin(); iter != projectiles.end();)
	{
		if ((*iter)->finished)
		{
			delete (*iter);
			iter = projectiles.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}
}

void Weapon::Draw()
{
	for (auto& iter : projectiles)
	{
		iter->Draw();
	}
}

std::list<Projectile*>& Weapon::GetProjectiles()
{
	return projectiles;
}

Sprite2* Weapon::GetIcon()
{
	return data->weaponIcon;
}

void Weapon::SetPlayer(const Player* player)
{
	this->player = player;
}
