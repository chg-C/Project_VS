#pragma once
#include "Effect.h"
#include "SpriteAnimation.h"

class SpriteEffect : public Effect
{
public:
	float width;
	float height;

	SpriteAnimation* sprites;
public:
	SpriteEffect(SpriteAnimation* sprites, float x, float y, float scale)
		: Effect(x, y, scale), sprites(sprites), width(0), height(0)
	{

	}
	virtual ~SpriteEffect()
	{
		if (sprites != nullptr)
		{
			delete sprites;
			sprites = nullptr;
		}
	}
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};