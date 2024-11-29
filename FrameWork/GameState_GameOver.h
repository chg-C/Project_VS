#pragma once
#include "GameState.h"

class Sprite2;
class GameState_GameOver : public GameState
{
	Sprite2* gameOver;

	float alphaGameOverImage;
	float alphaGameOverText;

	bool finished;
public:
	GameState_GameOver();
	~GameState_GameOver();
public:
	// GameState��(��) ���� ��ӵ�
	void EnterState() override;
	void Update() override;
	void Draw() override;
	void ExitState() override;
};

