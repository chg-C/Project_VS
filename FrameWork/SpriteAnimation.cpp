#include "Include.h"
#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(bool isLoop)
	: isLoop(isLoop), currentIndex(0), currentTime(0)
{

}

SpriteAnimation::SpriteAnimation(const SpriteAnimation& other)
	: SpriteAnimation(other.isLoop)
{
	for (auto& iter : other.sprites)
	{
		AnimationClip* spriteCopied = new AnimationClip(*iter);
		sprites.push_back(spriteCopied);
	}
}

SpriteAnimation::~SpriteAnimation()
{
	for (auto& iter : sprites)
	{
		SAFE_DELETE(iter);
	}
	sprites.clear();
}

void SpriteAnimation::Init()
{
}

void SpriteAnimation::Update(float speed)
{
	currentTime += TIME * speed;
 	if (currentTime >= (sprites[currentIndex]->nextAnimDelay))
	{
		if (IsEnd())
		{
			if (isLoop)
				currentIndex = 0;
		}
		else
		{
			++currentIndex;
		}

		currentTime = 0;
	}
}
