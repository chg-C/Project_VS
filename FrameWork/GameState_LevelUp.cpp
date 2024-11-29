#include "Include.h"
#include "GameState_LevelUp.h"

GameState_LevelUp::GameState_LevelUp()
	: frame(nullptr), iconFrame(nullptr)
{
	EnterState();
}

GameState_LevelUp::~GameState_LevelUp()
{
	ExitState();

	SAFE_DELETE(frame);
	SAFE_DELETE(iconFrame);
}

void GameState_LevelUp::EnterState()
{
	frame = new Sprite2();
	frame->Create("./resource/Img/Etc/square.png", false);
	iconFrame = new Sprite2();
	iconFrame->Create("./resource/Img/Etc/square.png", false);

	{
		int rv = rand() % 6;

		if (rv == 0)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
		}
		if (rv == 1)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
		}
		if (rv == 2)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
		}
		if (rv == 3)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
		}
		if (rv == 4)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
		}
		if (rv == 5)
		{
			selection[0] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_MAGICWAND);
			selection[1] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_WHIP);
			selection[2] = ResourceManager::GetInstance().GetWeaponData(ID_WEAPON_GARLIC);
		}
	}
}

void GameState_LevelUp::Update()
{
	for (int i = 0; i < 3; ++i)
	{
		if (KeyDown('1' + i) && (GetTickCount64() - key.KeyTime3 > 500))
		{
			GameManager::GetInstance().TempEarnWeapon(selection[i]);
			GameManager::GetInstance().TempExitState();

			key.KeyTime3 = GetTickCount64();
		}
	}
}

void GameState_LevelUp::Draw()
{
	frame->RenderStretch(0, 0, 380, 500, 1, 1, 0xff000000, false);

	dv_font.DrawString("Level Up!", 380, 100, 36, 18);

	int height = 110;
	char text[64];
	for (int i = -1; i <= 1; ++i)
	{
		iconFrame->RenderStretch(0, height * i, 360, 100, 1, 1, 0xff777777, false);
		selection[i + 1]->weaponIcon->RenderStretch(-150, (height * i) - 20, 50, 50, 1, 1, 0xffffffff, false);
		sprintf_s(text, "무기 선택하기: %d", i + 2);
		dv_font.DrawString(text, 320, 335 + height * i);
	}
}

void GameState_LevelUp::ExitState()
{
}
