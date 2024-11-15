#pragma once
class SelectArrow
{
	int arrowCount;
	Sprite arrowSprite[8];
	DWORD arrowSpinTime;
public:
	SelectArrow();
	~SelectArrow();
	void Init();
	void Update();
	void Render(float x, float y, float radian, float sx, float sy, int pivotMode=0);
	void Activate(bool isSelected);
};