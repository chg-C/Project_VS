#pragma once
#include "Include.h"
#include "Character.h"
#include "Projectile.h"
#include "ResourceManager.h"

#include <vector>
using std::vector;


class Player : public Character
{
	bool damaging;
	float dmgTime;

	float moveSpeed;
	float armor;

	int dir = 1;

	DWORD playerColor;
	int alpha = 0xff;

	Sprite2* squareSprite;

	char name[64];
public :
	Player(PlayerData* data);
	~Player();

	int GetDirection() const { return dir; }
	virtual void SetVelocity(D3DXVECTOR2 velocity);

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	void DrawHealthBar();

	virtual void Move(float x, float y);
	virtual void Damage(float dmg);

	const char* GetName() { return name; }
};