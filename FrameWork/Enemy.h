#pragma once
#include <vector>
using std::vector;

class Enemy : public Character
{
private:
	//Status
	float moveSpeed;
	float attackDamage;
	
	// Rendering
	int spriteIdx;
	float animSpeed;

	Sprite2* currentSprite;

	vector<Sprite2*> movingSprites;
	vector<Sprite2*> dyingSprites;
public:
	Enemy(float x, float y, float scale = 1);
	~Enemy();
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Move(float x, float y);
};

