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
	/// 화면 중앙을 0,0 축으로 맞춰서 그리기 /
	/// 캐릭터 등 중앙 축으로 작동하는 오브젝트들이 사용
	/// </summary>	
	void RenderStretch(float x, float y, float width, float height, float scaleX = 1, float scaleY = 1, DWORD color = 0xffffffff, bool useCam = true, float rotate = 0, RenderPivot pivot = PIVOT_CENTER);
};

