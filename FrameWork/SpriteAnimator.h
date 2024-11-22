#pragma once
#include "SpriteAnimation.h"

#include <unordered_map>

/// <summary>
/// 애니메이션 데이터 객체를 묶어서 관리하는 클래스
/// </summary>
class SpriteAnimator
{
private:
	std::unordered_map<int, SpriteAnimation*> animations;
	int currentKey;
public:
	SpriteAnimator();
	SpriteAnimator(const SpriteAnimator& other);
	~SpriteAnimator();
public:
	void Init();
	void Update(float speed = 1);

	void Reset()
	{
		animations[currentKey]->Reset();
	}
	bool IsEnd()
	{
		return animations[currentKey]->IsEnd();
	}

	void Insert(int key, SpriteAnimation* value)
	{
		animations[key] = value;
	}
	void ChangeAnimation(int key)
	{
		if (currentKey != key)
		{
			currentKey = key;
			animations[currentKey]->Reset();
		}
	}

	const SpriteData* GetCurrentSpriteData();
};