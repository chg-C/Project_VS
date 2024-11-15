#pragma once
#include "Include.h"
#include "Sprite2.h"
#include "Character.h"

#include <vector>
using std::vector;


class Player : public Character
{
	float speed;
	float gravity;

	bool grounded;

	bool moving;
	int idx = 0;

	int dir = 1;
public :
	Player();
	~Player();

	vector<Sprite2*>  idlingSprites;
	vector<Sprite2*>  movingSprites;

	Sprite2* currentSprite;

	DWORD m_PlayerTime;
	DWORD m_PlayerAnimTime;

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	virtual void Move(float x, float y);
};