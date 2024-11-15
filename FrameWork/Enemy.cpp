#include "Include.h"

Enemy::Enemy(float x, float y, float scale)
	: Character(x, y, scale), animSpeed(1), spriteIdx(0), moveSpeed(1), attackDamage(1)
{
}

Enemy::~Enemy()
{
	for (auto& sprite : movingSprites)
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
	movingSprites.clear();


	for (auto& sprite : dyingSprites)
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
	dyingSprites.clear();
}

void Enemy::Init()
{
	char FileName[256];

	Sprite2* sprite;
	for (int i = 0; i < 4; ++i)
	{
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/monster/bat/Bat3_Color_i%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		movingSprites.push_back(sprite);
	}
	for (int i = 0; i < 14; ++i)
	{
		sprite = new Sprite2();
		sprintf_s(FileName, "./resource/Img/monster/bat/Bat1_%d.png", i);
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		dyingSprites.push_back(sprite);
	}

	currentSprite = movingSprites[0];

	size.x = currentSprite->imagesinfo.Width * scale;
	size.y = currentSprite->imagesinfo.Height * scale;
}

void Enemy::Update()
{
	velocity.x = 0;
	velocity.y = 0;

	//이동 방향 계산
	D3DXVECTOR2 dir = GameManager::GetInstance().player->GetPos() - pos;
	D3DXVec2Normalize(&dir, &dir);
	dir *= moveSpeed;
	
	//이동 거리 저장
	velocity = dir;
}

void Enemy::Draw()
{
	currentSprite->RenderStretch(pos.x, pos.y, size.x, size.y, dir * 1, 1);
}
void Enemy::Move(float x, float y)
{
	//스프라이트 방향 설정
	if (x > 0)
		this->dir = -1;
	else
		this->dir = 1;

	pos.x += x;
	pos.y += y;
}
