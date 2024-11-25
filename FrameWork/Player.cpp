#include "Include.h"


Player::Player(PlayerData* data)
	: Character(0, 0, 1.5f), playerColor(0xffffffff), moveSpeed(1.5f), armor(0), damaging(false), dmgTime(0), squareSprite(nullptr)
{
	pos.x = 0;
	pos.y = 0;

	maxHP = currentHP = 100;

	int animatorID = 0;
	if (data != nullptr)
	{
		animatorID = data->animatorID;
		maxHP = data->maxHealth;
		currentHP = maxHP;
		moveSpeed = data->moveSpeed;
		armor = data->defense;
	}
	
	animator = ResourceManager::GetInstance().GetAnimator(animatorID);
}

Player::~Player()
{
	SAFE_DELETE(squareSprite);	
}

void Player::Init()
{
	char FileName[256] = {};
	sprintf_s(FileName, "./resource/Img/Etc/Square.png");
	squareSprite = new Sprite2();
	squareSprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
}

void Player::Update()
{
	dmgTime -= TIME;

	if (damaging && dmgTime <= 0)
	{
		playerColor |= 0xffff;
		damaging = false;
	}
	if (IsAlive())
	{


		//if (attackCooldown <= 0)
		//{
		//	attackCooldown = 1;
		//	Projectile* proj = new Projectile(attackEffectTemplate, pos.x + (100 * dir), pos.y, dir, 0.5f);
		//	proj->Init();
		//	projectiles.push_back(proj);
		//}

	}
	else if(currentState == CS_DYING)
	{
		alpha -= 5;
		playerColor &= (alpha<<24);

		if (alpha <= 0)
			currentState = CS_DEAD;
	}
	

	pos += velocity;

	//카메라 - 위치 동기화
	Camera::GetInstance().SetCamX(-pos.x);
	Camera::GetInstance().SetCamY(-pos.y);
	//

	switch (currentState)
	{
	case CS_IDLE:
	case CS_DYING:
	case CS_DEAD:
		animator->ChangeAnimation((int)CS_IDLE);
		break;
	case CS_MOVE:
		animator->ChangeAnimation((int)CS_MOVE);
		break;
	}

	animator->Update(moveSpeed);
	size.x = animator->GetCurrentSpriteData()->width * scale;
	size.y = animator->GetCurrentSpriteData()->height * scale;
}
void Player::SetVelocity(D3DXVECTOR2 velocity)
{
	if (!IsAlive())
		return;

	this->velocity = velocity * moveSpeed;
	if (D3DXVec2Length(&velocity) > 0)
	{
		currentState = CS_MOVE;
	}
	else
	{
		currentState = CS_IDLE;
	}

	if (velocity.x > 0)
	{
		dir = 1;
	}
	else if (velocity.x < 0)
	{
		dir = -1;
	}
}

void Player::Draw()
{
	animator->GetCurrentSpriteData()->sprite->RenderStretch(pos.x, pos.y, size.x, size.y, dir * 1, 1, playerColor);
	DrawHealthBar();
}

void Player::DrawHealthBar()
{
	//배경
	squareSprite->RenderStretch(pos.x, pos.y + 40, 50, 5, 1, 1, 0x88000000);

	float per = 50 * (currentHP / maxHP);
	if (per < 0) per = 0;
	//체력
	squareSprite->RenderStretch((pos.x + ((per/2)-25)), pos.y + 40, per, 5, 1, 1, 0xffff0000);
	//squareSprite->RenderStretch()
}

void Player::Move(float x, float y)
{
	
	pos.x += x;
	pos.y += y;
}

void Player::Damage(float dmg)
{
	//if (invTime > 0)
	//	return;
	if (IsAlive())
	{
		float dmgCal = dmg - armor;
		if (dmgCal < 0) dmgCal = 0;
		currentHP -= dmgCal;

		if (currentHP <= 0)
		{
			currentState = CS_DYING;

			velocity.x = 0;
			velocity.y = 0;
		}

		damaging = true;
		playerColor &= 0xffff0000;

		dmgTime = 0.15f;
	}
}
