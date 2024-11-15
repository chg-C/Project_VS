#pragma once

enum RenderPivot {PIVOT_LEFTTOP, PIVOT_CENTER};
class Sprite2 : public Sprite
{
public:
	~Sprite2();
public:
	void DrawStretch(float x, float y, float width, float height, DWORD color=0xffffffff, bool useCam = true, float rotate=0, RenderPivot pivot = PIVOT_LEFTTOP);
	void DrawStretchWithScale(float x, float y, float width, float height, float scaleX, float scaleY, DWORD color = 0xffffffff, bool useCam = true, float rotate = 0, RenderPivot pivot = PIVOT_LEFTTOP);
	
	/// <summary>
	/// ȭ�� �߾��� 0,0 ������ ���缭 �׸��� /
	/// ĳ���� �� �߾� ������ �۵��ϴ� ������Ʈ���� ���
	/// </summary>	
	void RenderStretch(float x, float y, float width, float height, float scaleX = 1, float scaleY = 1, DWORD color = 0xffffffff, bool useCam = true, float rotate = 0, RenderPivot pivot = PIVOT_CENTER);
};

