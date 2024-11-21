#include "Include.h"
#include "SpriteAnimator.h"



SpriteAnimator::SpriteAnimator()
    : currentKey()
{
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

const SpriteData* SpriteAnimator::GetCurrentSpriteData()
{
    return animations[currentKey]->GetCurrentSpriteData();
}
