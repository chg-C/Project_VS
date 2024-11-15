#include "Include.h"


Player::Player()
	:idx(0), moving(false)
{
	m_PlayerAnimTime = 0;
	pos.x = 0;
	pos.y = 0;

	gravity = 0;// 5.75f;
	grounded = false;
}

Player::~Player()
{
	for (auto& sprite : idlingSprites)
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
	idlingSprites.clear();


	for (auto& sprite : movingSprites)
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}
	movingSprites.clear();
}

void Player::Init()
{
	speed = 2;

	char FileName[256];
	

	Sprite2* sprite;
	for (int i = 0; i < 1; ++i)
	{
		sprite = new Sprite2();
		
		sprintf_s(FileName, "./resource/Img/player/newAntonio_%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		idlingSprites.push_back(sprite);

	}
	for (int i = 0; i < 8; ++i)
	{
		sprite = new Sprite2();

		sprintf_s(FileName, "./resource/Img/player/newAntonio_%02d.png", (i + 1));
		sprite->Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

		movingSprites.push_back(sprite);
	}

	currentSprite = idlingSprites[0];
	scale = 2;
}

void Player::Update()
{
	velocity.x = velocity.y = 0;
	moving = false;


	if(GetTickCount() - m_PlayerTime > 10)
	{
		m_PlayerTime = GetTickCount();
	}

	if (KeyDown(VK_LEFT) || KeyDown('A'))
	{
		dir = -1;
		velocity.x = -speed;

		moving = true;
	}
	else if (KeyDown(VK_RIGHT) || KeyDown('D'))
	{
		dir = 1;
		velocity.x = speed;

		moving = true;
	}
	if (KeyDown(VK_UP) || KeyDown('W'))
	{
		velocity.y = -speed;
		moving = true;
	}
	else if (KeyDown(VK_DOWN) || KeyDown('S'))
	{
		velocity.y = speed;
		moving = true;
	}

	if (KeyDown(VK_SPACE))
	{
		
	}


	if (moving == false)
	{
		idx = 0;
		currentSprite = idlingSprites[idx];
	}
	else
	{
		if (GetTickCount() - m_PlayerAnimTime > 100)
		{
			idx = (idx + 1) % 8;
			m_PlayerAnimTime = GetTickCount();

			currentSprite = movingSprites[idx];
		}
	}

	size.x = currentSprite->imagesinfo.Width * scale;
	size.y = currentSprite->imagesinfo.Height * scale;
}

void Player::Draw()
{
	currentSprite->RenderStretch(pos.x, pos.y, size.x, size.y, dir * 1, 1);
}

void Player::Move(float x, float y)
{
	pos.x += x;
	pos.y += y;

	//카메라 - 위치 동기화
	Camera::GetInstance().SetCamX(-pos.x);
	Camera::GetInstance().SetCamY(-pos.y);
}
