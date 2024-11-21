#include "Include.h"
#include "EffectManager.h"



EffectManager::~EffectManager()
{
	for (auto& iter : effects)
	{
		SAFE_DELETE(iter);
	}
	effects.clear();
}

void EffectManager::Init()
{
}

void EffectManager::Update()
{
	for (auto iter = effects.begin(); iter != effects.end();)
	{
		(*iter)->Update();

		if ((*iter)->finished)
		{
			SAFE_DELETE(*iter);
			iter = effects.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void EffectManager::Draw()
{
	for (auto& iter : effects)
	{
		iter->Draw();
	}
}

void EffectManager::RegisterEffect(Effect* effect)
{
	effects.push_back(effect);
}
