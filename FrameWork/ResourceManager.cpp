#include "Include.h"
#include "Cache.h"
#include "ResourceManager.h"

#define AnimationCache AutoDeleteCache<int, SpriteAnimation>::GetInstance()
#define AnimatorCache AutoDeleteCache<int, SpriteAnimator>::GetInstance()
#define PlayerDataCache AutoDeleteCache<int, PlayerData>::GetInstance()
#define EnemyDataCache AutoDeleteCache<int, EnemyData>::GetInstance()

enum AnimatorIDs { ID_PLAYER_ANTONIO, ID_ENEMY_BAT, ID_ENEMY_MUDMAN };
enum AnimationIDs { ID_EFFECT_WHIP };

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::InitResources()
{
	SpriteAnimator* animator = new SpriteAnimator();

	char FileName[256];

	SpriteAnimation* anim = new SpriteAnimation(true);
	SpriteData* data;
	Sprite2* sprite;
	for (int i = 0; i < 1; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/Game/player/newAntonio_%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.5f;
		data->color = 0xffffffff;
		data->SetWH();

		anim->Push(data);
	}
	animator->Insert(CS_IDLE, anim);

	anim = new SpriteAnimation(true);
	for (int i = 0; i < 8; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/Game/player/newAntonio_%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.15f;
		data->color = 0xffffffff;
		data->SetWH();

		anim->Push(data);
	}
	animator->Insert(CS_MOVE, anim);

	AnimatorCache.Put((int)ID_PLAYER_ANTONIO, animator);

	animator = new SpriteAnimator();
	anim = new SpriteAnimation(true);
	for (int i = 0; i < 4; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/Game/monster/bat/Bat3_Color_i%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.25f;
		data->color = 0xffffffff;
		data->SetWH();

		anim->Push(data);
	}
	animator->Insert(CS_IDLE, anim);


	anim = new SpriteAnimation(false);
	for (int i = 0; i < 14; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();
		sprintf_s(FileName, "./resource/Img/Game/monster/bat/Bat1_%d.png", i);
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.035f;
		data->color = 0xffffffff;
		data->SetWH();

		anim->Push(data);
	}
	animator->Insert(CS_DYING, anim);

	AnimatorCache.Put(ID_ENEMY_BAT, animator);

	//Mudman
	animator = new SpriteAnimator();
	anim = new SpriteAnimation(true);
	for (int i = 0; i < 4; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/Game/monster/mudman/Mudman1_i%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.25f;
		data->color = 0xffffffff;
		data->SetWH(1.25f);

		anim->Push(data);
	}
	animator->Insert(CS_IDLE, anim);


	anim = new SpriteAnimation(false);
	for (int i = 0; i < 14; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();
		sprintf_s(FileName, "./resource/Img/Game/monster/mudman/Mudman1_%d.png", i);
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->nextAnimDelay = 0.035f;
		data->color = 0xffffffff;
		data->SetWH(1.25f);

		anim->Push(data);
	}
	animator->Insert(CS_DYING, anim);

	AnimatorCache.Put(ID_ENEMY_MUDMAN, animator);
	//
	SpriteAnimation* attackEffectTemplate = new SpriteAnimation();
	for (int i = 0; i < 4; ++i)
	{
		data = new SpriteData();
		sprite = new Sprite2();
		sprintf_s(FileName, "./resource/Img/Game/effects/attack/War_Spr_Attack2Slash_000%d.png", i + 1);
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		data->sprite = sprite;
		data->willCollide = true;
		data->color = 0xffffffff;
		data->nextAnimDelay = 0.05f;
		data->SetWH();

		attackEffectTemplate->Push(data);
	}
	AnimationCache.Put((int)ID_EFFECT_WHIP, attackEffectTemplate);


	PlayerData* playerData = new PlayerData;
	playerData->animatorID = ID_PLAYER_ANTONIO;
	playerData->playerID = ID_PLAYER_ANTONIO;
	playerData->maxHealth = 200;
	playerData->attackPower = 10;	
	playerData->moveSpeed = 3;
	playerData->defense = 0;
	PlayerDataCache.Put(playerData->playerID, playerData);


	EnemyData* enemyData = new EnemyData;
	enemyData->enemyID = 0;
	enemyData->animatorID = ID_ENEMY_BAT;
	enemyData->attackPower = 2;
	enemyData->maxHealth = 8;
	enemyData->moveSpeed = 1.0f;

	EnemyDataCache.Put(0, enemyData);

	enemyData = new EnemyData;
	enemyData->enemyID = 1;
	enemyData->animatorID = ID_ENEMY_MUDMAN;
	enemyData->attackPower = 3;
	enemyData->maxHealth = 20;
	enemyData->moveSpeed = 0.5f;

	EnemyDataCache.Put(1, enemyData);
}

SpriteAnimation* ResourceManager::GetAnimation(int id)
{
	return AnimationCache.Get(id);
}

SpriteAnimator* ResourceManager::GetAnimator(int id)
{
	return AnimatorCache.Get(id);
}

PlayerData* ResourceManager::GetPlayerData(int id)
{
	return PlayerDataCache.Get(id);
}

EnemyData* ResourceManager::GetEnemyData(int id)
{
	return EnemyDataCache.Get(id);
}
