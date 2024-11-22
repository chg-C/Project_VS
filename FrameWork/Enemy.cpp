#include "Include.h"

Enemy::Enemy(EnemyData* data, float x, float y, float scale)
	: Character(x, y, scale), spriteIdx(0), moveSpeed(1), attackDamage(1), damageDelay(0), damaging(false)
{
	maxHP = currentHP = 15;

	int animatorID = ID_ENEMY_BAT;
	if (data != nullptr)
	{
		animatorID = data->animatorID;
		maxHP = data->maxHealth;
		currentHP = maxHP;
		moveSpeed = data->moveSpeed;
		attackDamage = data->attackPower;
	}

	animator = ResourceManager::GetInstance().GetAnimator(animatorID);
}

Enemy::~Enemy()
{
	SAFE_DELETE(animator);
}

void Enemy::Init()
{
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

	if (GameManager::GetInstance().GetPlayer()->GetPos().x - pos.x > 0)
		dir = -1;
	else
		dir = 1;
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
