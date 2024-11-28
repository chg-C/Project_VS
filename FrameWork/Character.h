#pragma once
#include <d3dx9.h>
#include "SpriteAnimator.h"

enum CharacterState {CS_IDLE, CS_MOVE, CS_DYING, CS_DEAD, CS_END};

/// <summary>
/// 캐릭터 베이스 클래스
/// 플레이어 / 몬스터가 상속해서 사용
/// </summary>
class Character
{
protected:
	Character() : pos(0, 0), dir(1), scale(1), currentState(CS_IDLE), currentHP(100), maxHP(100), animator(nullptr) {}
	Character(float x, float y, float scale = 1) : pos(x, y), dir(1), scale(scale), currentState(CS_IDLE), currentHP(100), maxHP(100), animator(nullptr) {}
protected:
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;

	int dir;
	float scale;

	float maxHP;
	float currentHP;

	SpriteAnimator* animator;
	CharacterState currentState;
public:
	virtual ~Character() { if (animator != nullptr) { delete animator; animator = nullptr; } }
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LateUpdate() {}
public:
	virtual void Move(float x, float y)
	{
		pos.x += x;
		pos.y += y;
	}
	void SetPos(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}
	D3DXVECTOR2 GetPos() const
	{
		return pos;
	}

	virtual void SetVelocity(D3DXVECTOR2 velocity) { this->velocity = velocity; }
	D3DXVECTOR2 GetVelocity() const { return velocity; }

	D3DXVECTOR2 GetSize() const { return size; }

	RECT GetCollider(float mp = 1) const { return RECT{
								(long)(pos.x - (size.x*mp / 2)),
								(long)(pos.y - (size.y*mp / 2)),
								(long)(pos.x + (size.x*mp / 2)),
								(long)(pos.y + (size.y*mp / 2)),
							}; }

	float Distance(Character& other)
	{
		return D3DXVec2Length(&(other.pos - this->pos));
	}
	bool IsAlive() { return !(currentState == CS_DYING || currentState == CS_DEAD); }
	CharacterState GetState() { return currentState; }

	virtual void Damage(float dmg) { currentHP -= dmg; }
};