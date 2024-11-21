#include "Include.h"
#include "SpriteEffect.h"

void SpriteEffect::Init()
{
	sprites->Init();
}

void SpriteEffect::Update()
{
	sprites->Update();
	if (sprites->IsEnd())
	{
		finished = true;
	}
	width = sprites->GetCurrentSpriteData()->sprite->imagesinfo.Width * scale;
	height = sprites->GetCurrentSpriteData()->sprite->imagesinfo.Height * scale;
}

void SpriteEffect::Draw()
{
	if (!finished)
		sprites->GetCurrentSpriteData()->sprite->RenderStretch(x, y, width, height, scale, scale, sprites->GetCurrentSpriteData()->color);
}
