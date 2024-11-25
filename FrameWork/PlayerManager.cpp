#include "Player.h"
#include "Projectile.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
	:player(nullptr)
{
}

PlayerManager::~PlayerManager()
{
	SAFE_DELETE(player);
	SAFE_DELETE(attackEffectTemplate);

	for (auto& iter : projectiles)
	{
		SAFE_DELETE(iter);
	}
	projectiles.clear();
}

void PlayerManager::Init(PlayerData* data)
{
	player = new Player(data);
	player->Init();

	attackEffectTemplate = ResourceManager::GetInstance().GetAnimation(ID_EFFECT_WHIP);
}

void PlayerManager::Update()
{
	if (player->IsAlive())
	{
		D3DXVECTOR2 velocity(0, 0);

		if (KeyDown(VK_LEFT) || KeyDown('A'))
		{
			velocity.x = -1;
		}
		else if (KeyDown(VK_RIGHT) || KeyDown('D'))
		{
			velocity.x = 1;
		}
		if (KeyDown(VK_UP) || KeyDown('W'))
		{
			velocity.y = -1;
		}
		else if (KeyDown(VK_DOWN) || KeyDown('S'))
		{
			velocity.y = 1;
		}

		player->SetVelocity(velocity);

		if (KeyDown(VK_SPACE))
		{
			Projectile* proj = new Projectile(attackEffectTemplate, player->GetPos().x + (100 * player->GetDirection()), player->GetPos().y,
				player->GetDirection(), 0.5f);//pos.x + (100 * dir), pos.y, dir, 0.5f);
			proj->Init();
			projectiles.push_back(proj);
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
	player->Update();
	//이동 처리
	//D3DXVECTOR2 velocity = player->GetVelocity();
	//player->Move(velocity.x, velocity.y);
}

void PlayerManager::Draw()
{
	player->Draw();
	for (auto& iter : projectiles)
	{
		iter->Draw();
		//(*iter)->Draw();
	}
}

bool PlayerManager::IsPlaying()
{
	return player->GetState() != CS_DEAD;
}

Player* PlayerManager::GetPlayer()
{
	return player;
}

D3DXVECTOR2 PlayerManager::GetPlayerPos()
{
	return player->GetPos();
}

std::list<Projectile*>& PlayerManager::GetProjectiles()
{
	return projectiles;
}
