#include "Player.h"
#include "Weapon.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
	:player(nullptr), squareSprite(nullptr), tmpIdx(ID_PLAYER_BEGIN+1)
{
}

PlayerManager::~PlayerManager()
{
	SAFE_DELETE(player);

	for (auto& iter : weapons)
	{
		SAFE_DELETE(iter);
	}
	weapons.clear();

	SAFE_DELETE(squareSprite);
}

void PlayerManager::Init(PlayerData* data)
{
	player = new Player(data);
	player->Init();

	char FileName[256] = {};
	sprintf_s(FileName, "./resource/Img/Etc/Square.png");
	squareSprite = new Sprite2();
	squareSprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	Weapon* w = new Weapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC_LVL5), player);
	w->Init();
	weapons.push_back(w);
	w = new Weapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP_LVL1), player);
	w->Init();
	weapons.push_back(w);
	w = new Weapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_STAFF_LVL1), player);
	w->Init();
	weapons.push_back(w);
}

void PlayerManager::Update()
{
	keyDelay -= TIME;
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

		if (KeyDown('4') && keyDelay <= 0)
		{
			keyDelay = 2;

			tmpIdx += 1;
			if (tmpIdx >= ID_PLAYER_END)
				tmpIdx = ID_PLAYER_BEGIN + 1;
			SAFE_DELETE(player);
			
			PlayerData* data = ResourceManager::GetInstance().GetPlayerData(tmpIdx);

			player = new Player(data);
			player->Init();

			for (auto& iter : weapons)
			{
				iter->SetPlayer(player);
			}
		}

		player->SetVelocity(velocity);
	}
	player->Update();

	for (auto& iter : weapons)
	{
		iter->Update();
	}
	//이동 처리
	//D3DXVECTOR2 velocity = player->GetVelocity();
	//player->Move(velocity.x, velocity.y);
}

void PlayerManager::Draw()
{
	//XP
	squareSprite->DrawStretch(0, 0, SCREEN_WITH, 30, 0xff111111, false);
	float xpGauge = 50;
	squareSprite->DrawStretch(0, 0, xpGauge, 30, 0xff1111ff, false);

	//Inventory
	
	float x = 0;
	float y = 32;
	for (int i = 0; i < 6; ++i)
	{
		squareSprite->DrawStretch(x, y, 30, 30, 0xff000000, false);
		x += 32;
	}

	//
	player->Draw();
	
	x = 0;

	for (auto& iter : weapons)
	{
		iter->Draw();
		iter->GetIcon()->DrawStretch(x, y, 30, 30, 0xffffffff, false);

		x += 32;
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

const char* PlayerManager::GetPlayerName()
{
	return player->GetName();
}
std::list<Weapon*>& PlayerManager::GetWeapons()
{
	return weapons;
}

//TEMP
void PlayerManager::EarnWeapon(WeaponData* data)
{
	
}
//
//std::list<Projectile*>& PlayerManager::GetProjectiles()
//{
//	return projectiles;
//}
