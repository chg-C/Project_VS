#include "Include.h"

Enemy::Enemy(float x, float y, float scale)
	: Character(x, y, scale), animSpeed(1), spriteIdx(0), moveSpeed(1), attackDamage(1)
{
}

Enemy::~Enemy()
{
	SAFE_DELETE(animator);
}

void Enemy::Init()
{
	animator = new SpriteAnimator();

	char FileName[256];

	SpriteData* data;
	Sprite2* sprite;

	SpriteAnimation* anim = new SpriteAnimation(true);
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

	damageDelay = 0;

	currentHP = 15;
	maxHP = 15;
}

void Enemy::Update()
{
	damageDelay -= TIME;
	if (damaging && damageDelay <= 0)
	{
		damaging = false;
	}

	if (IsAlive())
	{
		if (!damaging)
		{
			velocity.x = 0;
			velocity.y = 0;

			//이동 방향 계산
			D3DXVECTOR2 dir = GameManager::GetInstance().GetPlayer()->GetPos() - pos;
			D3DXVec2Normalize(&dir, &dir);
			dir *= moveSpeed;

			//이동 거리 저장
			velocity = dir;
		}
		else
		{
			velocity.x = 0;
			velocity.y = 0;
		}
	}
	else
	{
		if (animator->IsEnd())
		{
			currentState = CS_DEAD;
		}
	}

	switch (currentState)
	{
	case CS_IDLE:
	case CS_MOVE:
		animator->ChangeAnimation((int)CS_IDLE);
		break;
	case CS_DYING:
	case CS_DEAD:
		animator->ChangeAnimation((int)CS_DYING);
		break;
	}

	animator->Update();
	size.x = animator->GetCurrentSpriteData()->width * scale;
	size.y = animator->GetCurrentSpriteData()->height * scale;
}

void Enemy::Draw()
{
	DWORD color = 0xffffffff;
	if (damaging)
		color = 0xffff0000;
	animator->GetCurrentSpriteData()->sprite->RenderStretch(pos.x, pos.y, size.x, size.y, dir * 1, 1, color);
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

void Enemy::Damage(float dmg)
{
	currentHP -= dmg;
	if (currentHP <= 0)
	{
		currentState = CS_DYING;
		animator->Reset();
	}
	else
	{
		damaging = true;
		damageDelay = 0.5f;
	}
}
