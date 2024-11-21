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
	/// 해당 좌표의 객체가 화면 밖으로 나갔는지 여부 확인
	/// </summary>
	/// <param name="x">x축 좌표</param>
	/// <param name="y">y축 좌표</param>
	/// <param name="tolerance">안전 거리, 이 수치만큼은 화면 밖에 있어도 false 리턴</param>
	/// <returns>화면 밖에 있다면 true</returns>
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