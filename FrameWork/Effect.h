#pragma once

class Effect
{
public:
	bool finished;

	float x;
	float y;

	float scale;
public:
	Effect(float x, float y, float scale) 
		:	finished(false), x(x), y(y), scale(scale)
	{

	}
	virtual ~Effect() {}
public:
	virtual void Init() {}
	virtual void Update() { finished = true; }
	virtual void Draw() {}
};