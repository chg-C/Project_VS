#pragma once
#include "GameState.h"

class GameState_LevelUp : public GameState
{
public:
	// GameState을(를) 통해 상속됨
	void EnterState() override;
	void Update() override;
	void Draw() override;
	void ExitState() override;
};

