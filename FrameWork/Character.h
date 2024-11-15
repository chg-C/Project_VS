#pragma once
#include <math.h>

/// <summary>
/// 캐릭터 베이스 클래스
/// 플레이어 / 몬스터가 상속해서 사용
/// </summary>
class Character
{
protected:
	Character() : pos(0, 0), dir(1), scale(1) {}
	Character(float x, float y, float scale = 1) : pos(x, y), dir(1), scale(scale) {}
protected:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;

	D3DXVECTOR2 velocity;

	int dir;
	float scale;

	float maxHP;
	float currentHP;
public:
	virtual ~Character() {}
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	virtual void Move(float x, float y)
	{
		pos.x += x;
		pos.y += y;
	}
	D3DXVECTOR2 GetPos()
	{
		return pos;
	}

	void SetVelocity(D3DXVECTOR2 velocity) { this->velocity = velocity; }
	D3DXVECTOR2 GetVelocity() { return velocity; }

	D3DXVECTOR2 GetSize() { return size; }

	RECT GetCollider(float mp = 1) { return RECT{
								(long)(pos.x - (size.x*mp / 2)),
								(long)(pos.y - (size.y*mp / 2)),
								(long)(pos.x + (size.x*mp / 2)),
								(long)(pos.y + (size.y*mp / 2)),
							}; }

	float Distance(Character& other)
	{
		
	}
};