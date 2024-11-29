#pragma once
#include "GameState.h"

class GameState_LevelUp : public GameState
{
private:
	//
	Sprite2* frame;
	Sprite2* iconFrame;
	//
	WeaponData* selection[3];
public:
	GameState_LevelUp();
	~GameState_LevelUp();
public:
	// GameState을(를) 통해 상속됨
	void EnterState() override;
	void Update() override;
	void Draw() override;
	void ExitState() override;
};

