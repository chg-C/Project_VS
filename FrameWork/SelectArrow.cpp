#include "Include.h"
#include "SelectArrow.h"
SelectArrow::SelectArrow()
{
	arrowSpinTime = 0;
	arrowCount = 0;
	for (int i = 0; i < 8; i++)
	{
		char filename[100];
		sprintf(filename, "./resource/Img/Arrow/arrow_0%d.png", i);

		// 생성한 파일 이름을 사용하여 버튼 이미지를 생성합니다.
		arrowSprite[i].Create(filename, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	
}
SelectArrow::~SelectArrow()
{


}

void SelectArrow::Update()
{
	if (GetTickCount() - arrowSpinTime > 100)
	{
		arrowCount++;
		arrowCount %= 8;
		arrowSpinTime = GetTickCount();
	}
}

void SelectArrow::Render(float x, float y, float radian, float sx, float sy, int pivotMode)
{
	
	arrowSprite[arrowCount].Render(x,y,radian,sx,sy,pivotMode);
}

void SelectArrow::Activate(bool isActivated)
{
	if (!isActivated)
	{
		arrowSprite[arrowCount].SetColor(255, 255, 255, 0);
	}
	else
	{
		arrowSprite[arrowCount].SetColor(255, 255, 255, 255);
	}
}