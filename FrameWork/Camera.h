#pragma once
#include "Singleton.h"
#include "CustomDefine.h"

class Camera : public Singleton<Camera>
{
	friend class Singleton<Camera>;
public:
	Camera()
		:camX(0), camY(0)
	{

	}
	~Camera()
	{

	}
private:
	float camX;
	float camY;
public:
	void MoveCamX(float x)
	{
		camX += x;
	}
	void MoveCamY(float y)
	{
		camY += y;
	}
	void SetCamX(float x) { camX = x; }
	void SetCamY(float y) { camY = y; }
	float GetCamX() { return camX; }
	float GetCamY() { return camY; }

	/// <summary>
	/// �ش� ��ǥ�� ��ü�� ȭ�� ������ �������� ���� Ȯ��
	/// </summary>
	/// <param name="x">x�� ��ǥ</param>
	/// <param name="y">y�� ��ǥ</param>
	/// <param name="tolerance">���� �Ÿ�, �� ��ġ��ŭ�� ȭ�� �ۿ� �־ false ����</param>
	/// <returns>ȭ�� �ۿ� �ִٸ� true</returns>
	bool IsOutOfScreen(float x, float y, float tolerance = 100)
	{
		float w = SCREEN_WITH / 2;
		float h = SCREEN_HEIGHT / 2;

		if (abs(-camX - x)-tolerance > w)
		{
			return true;
		}
		if (abs(-camY - y)-tolerance > h)
		{
			return true;
		}

		return false;
	}
	D3DXVECTOR2 ToScreenPos(D3DXVECTOR2 worldPos)
	{
		return D3DXVECTOR2(worldPos.x+camX, worldPos.y+camY);
	}
};