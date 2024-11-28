#pragma once

#include "Sprite2.h"
#include <vector>
using std::vector;


struct AnimationClip
{
	AnimationClip() 
	{
	}
	AnimationClip(const AnimationClip& other)
	{
		sprite = new Sprite2(*other.sprite);

		hasCollision = other.hasCollision;

		width = other.width;
		height = other.height;
		color = other.color;

		nextAnimDelay = other.nextAnimDelay;
	}
	~AnimationClip()
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	bool hasCollision;

	float width;
	float height;

	float nextAnimDelay;
	DWORD color;

	Sprite2* sprite;

	void SetWH(float mp = 1)
	{
		if (sprite != nullptr)
		{
			width = sprite->imagesinfo.Width * mp;
			height = sprite->imagesinfo.Height * mp;
		}
	}
};

/// <summary>
/// 애니메이션 데이터 객체
/// </summary>
class SpriteAnimation
{
public:
	SpriteAnimation(bool isLoop = false);
	SpriteAnimation(const SpriteAnimation& other);
	~SpriteAnimation();
private:
	bool isLoop;
	int currentIndex;

	float currentTime;
	vector<AnimationClip*> sprites;
public:
	void Init();
	void Update(float speed = 1);

	void Reset()
	{
		currentIndex = 0;
		currentTime = 0;
	}

	void Push(AnimationClip* data)
	{
		sprites.push_back(data);
	}

	bool IsEnd() { return currentIndex >= sprites.size()-1; }
	const AnimationClip* GetCurrentSpriteData() { return sprites[currentIndex]; }
};