#pragma once

#include "Sprite2.h"
#include <vector>
using std::vector;


struct SpriteData
{
	SpriteData() 
	{
	}
	SpriteData(const SpriteData& other)
	{
		sprite = new Sprite2(*other.sprite);

		willCollide = other.willCollide;

		width = other.width;
		height = other.height;
		color = other.color;

		nextAnimDelay = other.nextAnimDelay;
	}
	~SpriteData()
	{
		if (sprite != nullptr)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	bool willCollide;

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
	vector<SpriteData*> sprites;
public:
	void Init();
	void Update(float speed = 1);

	void Reset()
	{
		currentIndex = 0;
		currentTime = 0;
	}

	void Push(SpriteData* data)
	{
		sprites.push_back(data);
	}

	bool IsEnd() { return currentIndex >= sprites.size()-1; }
	const SpriteData* GetCurrentSpriteData() { return sprites[currentIndex]; }
};