#pragma once
#include "GameState.h"

class GameState_LevelUp : public GameState
{
public:
	// GameState��(��) ���� ��ӵ�
	void EnterState() override;
	void Update() override;
	void Draw() override;
	void ExitState() override;
};

