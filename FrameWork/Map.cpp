#include "Include.h"
#include "CustomDefine.h"

Map::Map()
	:bg_width(1024), bg_height(1024)
{
	m_Stage = 1;
}

Map::~Map()
{
}


void Map::Init()
{
	char FileName[256];
	
	sprintf_s(FileName, "./resource/Img/map1/map_bg.png");

	map.Create(FileName, false, 0);
	/*for (int i = 0; i < 4; ++i)
	{
		map[i].Create(FileName, false, 0);
	}*/

	bg_width = MAPSIZE_X;
	bg_height = MAPSIZE_Y;

}

void Map::Update()
{
	//Map Scroll
	float x = Camera::GetInstance().GetCamX();
	float y = Camera::GetInstance().GetCamY();
	
	while(abs(x) > MAPSIZE_X)
	{
		if (x > MAPSIZE_X)
		{
			x -= MAPSIZE_X * 2;
		}
		if (x < -MAPSIZE_X)
		{
			x += MAPSIZE_X * 2;
		}
	}
	while (abs(y) > MAPSIZE_Y)
	{
		if (y > MAPSIZE_Y)
		{
			y -= MAPSIZE_Y * 2;
		}
		if (y < -MAPSIZE_Y)
		{
			y += MAPSIZE_Y * 2;
		}
	}

	scrollX = x;
	scrollY = y;
}
void Map::Draw()
{
	//map.Draw(0, 0);
	DrawMapBlock(0, 0);

	//상하좌우 스크롤
	DrawMapBlock(-MAPSIZE_X * 2, 0);
	DrawMapBlock(MAPSIZE_X * 2, 0);
	DrawMapBlock(0, MAPSIZE_Y*2);
	DrawMapBlock(0, -MAPSIZE_Y*2);

	//대각선 스크롤
	DrawMapBlock(-MAPSIZE_X * 2, MAPSIZE_Y * 2);
	DrawMapBlock(-MAPSIZE_X * 2, -MAPSIZE_Y * 2);
	DrawMapBlock(MAPSIZE_X * 2, MAPSIZE_Y * 2);
	DrawMapBlock(MAPSIZE_X * 2, -MAPSIZE_Y * 2);
}

void Map::DrawMapBlock(float x, float y)
{
	//Camera 대신 자체 Scroll 값 사용
	map.RenderStretch(x+scrollX, y+scrollY, bg_width * 2, bg_height * 2, 1, 1, 0xffffffff, false, 0, PIVOT_CENTER);
}
