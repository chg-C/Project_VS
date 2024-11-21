#pragma once
#include "Effect.h"
#include <functional>

class TextEffect : public Effect
{
public:
	char* texts;
	float lifeTime;
	std::function<void()> animation;
public:
	TextEffect(float x, float y, float scale, const char* texts, float lifeTime);
	virtual ~TextEffect();
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
};