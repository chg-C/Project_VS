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
};