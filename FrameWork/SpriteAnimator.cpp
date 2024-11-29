#include "Include.h"
#include "SpriteAnimator.h"



SpriteAnimator::SpriteAnimator()
    : currentKey()
{
}

SpriteAnimator::SpriteAnimator(const SpriteAnimator& other)
    :currentKey(other.currentKey)
{
    for (auto& iter : other.animations)
    {
        SpriteAnimation* anim = new SpriteAnimation(*iter.second);
        animations[iter.first] = anim;
    }
}

SpriteAnimator::~SpriteAnimator()
{
    for (auto& iter : animations)
    {
        SAFE_DELETE(iter.second);
    }
    animations.clear();
}

void SpriteAnimator::Init()
{
}

void SpriteAnimator::Update(float speed)
{
    animations[currentKey]->Update(speed);
}

const AnimationClip* SpriteAnimator::GetCurrentSpriteData()
{
    return animations[currentKey]->GetCurrentSpriteData();
}
