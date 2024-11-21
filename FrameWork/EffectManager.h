#pragma once

#include <list>
using std::list;

class Effect;

class EffectManager
{
	list<Effect*> effects;
public:
	~EffectManager();
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
public:
	void RegisterEffect(Effect* effect);
};

