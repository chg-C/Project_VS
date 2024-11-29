#pragma once
#include "Gamestate.h"

class GameState_Clear : public GameState 
{
private:
	Enemy* boss;

	Sprite2* gameOver;

	float alphaGameOverImage;
	float alphaGameOverText;

	bool finished;
public:
	GameState_Clear(Enemy* boss);
	~GameState_Clear();
public:
	// GameState��(��) ���� ��ӵ�
	void EnterState() override;
	void Update() override;
	void Draw() override;
	void ExitState() override;
};

