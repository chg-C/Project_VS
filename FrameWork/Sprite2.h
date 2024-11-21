#pragma once

enum RenderPivot {PIVOT_LEFTTOP, PIVOT_CENTER};
class Sprite2
{
public:
	IDirect3DTexture9* Texture;
	D3DXIMAGE_INFO imagesinfo;
public:
	Sprite2() : Texture(nullptr), imagesinfo() {}
	Sprite2(const Sprite2& other) : Sprite2() {
		this->Texture = other.Texture;
		this->imagesinfo = other.imagesinfo;
	}
	~Sprite2();
public:
	bool Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor);

	void DrawStretch(float x, float y, float width, float height, DWORD color=0xffffffff, bool useCam = true, float rotate=0, RenderPivot pivot = PIVOT_LEFTTOP);
	void DrawStretchWithScale(float x, float y, float width, float height, float scaleX, float scaleY, DWORD color = 0xffffffff, bool useCam = true, float rotate = 0, RenderPivot pivot = PIVOT_LEFTTOP);
	
	/// <summary>
	/// ȭ�� �߾��� 0,0 ������ ���缭 �׸��� /
	/// ĳ���� �� �߾� ������ �۵��ϴ� ������Ʈ���� ���
	/// </summary>	
	void RenderStretch(float x, float y, float width, float height, float scaleX = 1, float scaleY = 1, DWORD color = 0xffffffff, bool useCam = true, float rotate = 0, RenderPivot pivot = PIVOT_CENTER);
};

