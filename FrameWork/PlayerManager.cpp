#include "Player.h"
#include "Weapon.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
	:player(nullptr), squareSprite(nullptr), tmpIdx(ID_PLAYER_BEGIN+1), keyDelay(0)
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

	Weapon* w = new Weapon(ResourceManager::GetInstance().GetWeaponData(data->defaultWeaponID), player);
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
			keyDelay = 1;

			tmpIdx += 1;
			if (tmpIdx >= ID_PLAYER_END)
				tmpIdx = ID_PLAYER_BEGIN + 1;
			SAFE_DELETE(player);
			
			PlayerData* data = ResourceManager::GetInstance().GetPlayerData(tmpIdx);

			player = new Player(data);
			player->Init();

			for (auto& iter : weapons)
			{
				SAFE_DELETE(iter);
			}
			weapons.clear();

			EarnWeapon(ResourceManager::GetInstance().GetWeaponData(data->defaultWeaponID));
		}
		if (KeyDown('5') && keyDelay <= 0)
		{
			keyDelay = 1;

			EarnWeapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP));
		}
		if (KeyDown('6') && keyDelay <= 0)
		{
			keyDelay = 1;

			EarnWeapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC));
		}
		if (KeyDown('7') && keyDelay <= 0)
		{
			keyDelay = 1;

			EarnWeapon(ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND));
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
	player->Draw();

	DrawInventory();
}
void PlayerManager::DrawInventory()
{
	//Inventory
	float x = 0;
	float y = 32;
	for (int i = 0; i < 6; ++i)
	{
		squareSprite->DrawStretch(x, y, 30, 30, 0xff000000, false);
		x += 32;
	}
	x = 0;

	for (auto& iter : weapons)
	{
		iter->Draw();
		iter->GetIcon()->DrawStretch(x, y, 30, 30, 0xffffffff, false);
		char lvl[6];
		sprintf_s(lvl, "%d", iter->GetLevel());

		dv_font.DrawString(lvl, x, y, 12, 12, 500, 0xffffffff);

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
	bool haveOne = false;

	for (auto& iter : weapons)
	{
		if (iter->GetWeaponID() == data->weaponID)
		{
			haveOne = true;
			iter->LevelUp();

			break;
		}
	}

	if (!haveOne)
	{
		Weapon* w = new Weapon(data, player);
		w->Init();
		weapons.push_back(w);
	}
}
//
//std::list<Projectile*>& PlayerManager::GetProjectiles()
//{
//	return projectiles;
//}
