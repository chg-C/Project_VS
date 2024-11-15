#pragma once
class UISprite:public Sprite
{
public:
	UISprite();
	~UISprite();
	void UIRender(float x, float y, float radian, float sx, float sy, int pivotMode, DWORD setColor=0xffffffff);
};