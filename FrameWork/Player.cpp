#include "Include.h"


Player::Player(PlayerData* data)
	: Character(0, 0, 1.5f), moving(false), playerColor(0xffffffff), attackCooldown(0), moveSpeed(1.5f), armor(0)
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
	
	animator = new SpriteAnimator(*ResourceManager::GetInstance().GetAnimator(animatorID));
	attackEffectTemplate = new SpriteAnimation(*ResourceManager::GetInstance().GetAnimation(0));
}

Player::~Player()
{
	SAFE_DELETE(attackEffectTemplate);
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
	attackCooldown -= TIME;

	if (damaging && dmgTime <= 0)
	{
		playerColor |= 0xffff;
		damaging = false;
	}
	if (IsAlive())
	{
		velocity.x = velocity.y = 0;
		moving = false;

		if (KeyDown(VK_LEFT) || KeyDown('A'))
		{
			dir = -1;
			velocity.x = -moveSpeed;

			moving = true;
		}
		else if (KeyDown(VK_RIGHT) || KeyDown('D'))
		{
			dir = 1;
			velocity.x = moveSpeed;

			moving = true;
		}
		if (KeyDown(VK_UP) || KeyDown('W'))
		{
			velocity.y = -moveSpeed;
			moving = true;
		}
		else if (KeyDown(VK_DOWN) || KeyDown('S'))
		{
			velocity.y = moveSpeed;
			moving = true;
		}

		if (KeyDown(VK_SPACE))
		{
			attackCooldown = 1;
			Projectile* proj = new Projectile(attackEffectTemplate, pos.x + (100 * dir), pos.y, dir, 0.5f);
			proj->Init();
			projectiles.push_back(proj);
		}


		if (attackCooldown <= 0)
		{
			attackCooldown = 1;
			Projectile* proj = new Projectile(attackEffectTemplate, pos.x + (100 * dir), pos.y, dir, 0.5f);
			proj->Init();
			projectiles.push_back(proj);
		}
		if (moving == false)
		{
			currentState = CS_IDLE;
		}
		else
		{
			currentState = CS_MOVE;
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
	else if(currentState == CS_DYING)
	{
		alpha -= 5;
		playerColor &= (alpha<<24);

		if (alpha <= 0)
			currentState = CS_DEAD;
	}
	
	

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

void Player::Draw()
{
	animator->GetCurrentSpriteData()->sprite->RenderStretch(pos.x, pos.y, size.x, size.y, dir * 1, 1, playerColor);

	for (auto& iter : projectiles)
	{
		iter->Draw();
		//(*iter)->Draw();
	}

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
