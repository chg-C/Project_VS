#pragma once

class GameState
{
public:
	virtual void EnterState() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ExitState() = 0;
};