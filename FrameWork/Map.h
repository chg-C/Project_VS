#pragma once
#include "Include.h"
#include "Sprite2.h"

class Map
{
public:
	Map();
	~Map();

	Sprite2* map;

	float bg_width;
	float bg_height;

	float scrollX;
	float scrollY;

	/*Sprite m_MapImg1_1[6];
	Sprite m_MapImg1_2[45];*/
	/*DWORD m_MapImg1_1_ani1;
	int m_MapImg1_1_ani1Count;*/

	int m_Stage;

	void Init(const char* fileName);
	void Update();
	void Draw();

	void DrawMapBlock(float x, float y);
};