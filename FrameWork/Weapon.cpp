#include "Include.h"
#include "Projectile.h"
#include "MovingProjectile.h"
#include "LoopProjectile.h"
#include "Weapon.h"


Weapon::Weapon(const WeaponData* data, const Player* player)
	: data(data), player(player), generating(false), projectileCount(0), delay(1), currentLevel(1)
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
	delay = data->stats[(currentLevel - 1)]->delay;//data->delay;

	if (data->type == WEAPON_LOOP)
	{
		Projectile* p = new LoopProjectile(ResourceManager::GetInstance().GetAnimation(data->projectileID),
			data->stats[(currentLevel - 1)]->damage, data->stats[(currentLevel - 1)]->delay, 1.5f * data->stats[(currentLevel - 1)]->scale, player);
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
						player->GetDirection() * tempDir, data->stats[(currentLevel - 1)]->damage, 3.0f, 0.5f * data->stats[(currentLevel - 1)]->scale);//pos.x + (100 * dir), pos.y, dir, 0.5f);
					proj->Init();
					projectiles.push_back(proj);
					//Projectile* projectile = new Projectile()

					projectileCount++;

					if (projectileCount >= data->stats[(currentLevel - 1)]->projectileCount)
					{
						delay = data->stats[(currentLevel - 1)]->delay;
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
						if (D3DXVec2Length(&dir) <= ((WeaponStatusData_Move*)data->stats[(currentLevel - 1)])->range)
						{

							Projectile* proj = new MovingProjectile(ResourceManager::GetInstance().GetAnimation(data->projectileID),
								player->GetPos().x, player->GetPos().y, dir, data->stats[(currentLevel - 1)]->damage,
								((WeaponStatusData_Move*)data->stats[(currentLevel - 1)])->range, ((WeaponStatusData_Move*)data->stats[(currentLevel - 1)])->speed,
								((WeaponStatusData_Move*)data->stats[(currentLevel - 1)])->lifetime);
							proj->Init();
							projectiles.push_back(proj);

							projectileCount++;

							if (projectileCount >= data->stats[(currentLevel - 1)]->projectileCount)
							{
								delay = data->stats[(currentLevel - 1)]->delay;
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

void Weapon::LevelUp()
{
	if (currentLevel < data->maxLevel)
	{
		++currentLevel;


		for (auto& iter : projectiles)
		{
			SAFE_DELETE(iter);
		}
		projectiles.clear();

		Init();
	}
}
