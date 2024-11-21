#include "Include.h"
#include "Sprite2.h"
#include "Cache.h"


#define TextureCache AutoDeleteCache<std::string, TextureData>::GetInstance()

Sprite2::~Sprite2()
{
}

bool Sprite2::Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor)
{
	std::string key = std::string(filename);

	TextureData* data =	TextureCache.Get(key);
	if (data != nullptr)
	{
		Texture = data->Texture;
		imagesinfo = data->imagesinfo;
	}
	else
	{
		D3DXGetImageInfoFromFile(filename, &imagesinfo);

		HRESULT hr = E_FAIL;

		D3DCOLOR transparencycolor;
		if (bUseTransparency)	transparencycolor = TransparencyColor | 0xff000000;
		else					transparencycolor = 0;

		hr = D3DXCreateTextureFromFileEx(dv_font.Device9,
			filename, imagesinfo.Width, imagesinfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, transparencycolor, &imagesinfo, NULL, &Texture);

		data = new TextureData();
		data->Texture = Texture;
		data->imagesinfo = imagesinfo;

		TextureCache.Put(key, data);
	}
	return TRUE;

	/*
	hr = D3DXCreateTextureFromFileEx( font.Device9 ,
		filename , D3DX_DEFAULT , D3DX_DEFAULT , 1 , 0 , 	D3DFMT_UNKNOWN , D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE, 	D3DX_FILTER_NONE, transparencycolor,	NULL , 	NULL, 	&Texture ) ;

	return TRUE;
	*/

}
void Sprite2::DrawStretch(float x, float y, float width, float height, DWORD color, bool useCam, float rotate, RenderPivot pivot)
{
	if (useCam)
	{
		x += Camera::GetInstance().GetCamX();
		y += Camera::GetInstance().GetCamY();
	}

	ID3DXSprite* pSprite;

	pSprite = dv_font.Sprite;

	//D3DXVECTOR3 position( (float)x, (float)y, 1.0f ) ;

/*	Rect.left   = 0 ;
	Rect.top    = 0 ;
	Rect.right  = Rect.left + imagesinfo.Width ;
	Rect.bottom = Rect.top  + imagesinfo.Height ;
*/
	RECT Rect = { 0, 0, imagesinfo.Width, imagesinfo.Height };									   // sx 0 : 없어짐, 1 : 그대로, 2 : x축으로 2배 확대

	D3DXVECTOR3 center;

	if (pivot == PIVOT_LEFTTOP)
	{
		center.x = 0;
		center.y = 0;
	}
	else if (pivot == PIVOT_CENTER)
	{
		center.x = imagesinfo.Width / 2;
		center.y = imagesinfo.Height / 2;
	}
	center.z = 1;

	float sx = width / imagesinfo.Width;
	float sy = height / imagesinfo.Height;

	D3DXMATRIX trans, rotation, scale;
	D3DXMatrixScaling(&scale, sx, sy, 1);
	D3DXMatrixRotationZ(&rotation, rotate);
	D3DXMatrixTranslation(&trans, x, y, 1.0f);
	pSprite->SetTransform(&(scale * rotation * trans));

	dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->Draw(Texture, &Rect, &center, NULL, color);
	pSprite->Flush();
	dv_font.Sprite->End();

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	pSprite->SetTransform(&identity);
}

void Sprite2::DrawStretchWithScale(float x, float y, float width, float height, float scaleX, float scaleY, DWORD color, bool useCam, float rotate, RenderPivot pivot)
{
	if (useCam)
	{
		x += Camera::GetInstance().GetCamX();
		y += Camera::GetInstance().GetCamY();
	}

	ID3DXSprite* pSprite;

	pSprite = dv_font.Sprite;

	//D3DXVECTOR3 position( (float)x, (float)y, 1.0f ) ;

/*	Rect.left   = 0 ;
	Rect.top    = 0 ;
	Rect.right  = Rect.left + imagesinfo.Width ;
	Rect.bottom = Rect.top  + imagesinfo.Height ;
*/
	RECT Rect = { 0, 0, imagesinfo.Width, imagesinfo.Height };									   // sx 0 : 없어짐, 1 : 그대로, 2 : x축으로 2배 확대

	D3DXVECTOR3 center;
	if (pivot == PIVOT_LEFTTOP)
	{
		center.x = 0;
		center.y = 0;
	}
	else if (pivot == PIVOT_CENTER)
	{
		center.x = imagesinfo.Width / 2;
		center.y = imagesinfo.Height / 2;
	}
	center.z = 1;

	float sx = width / imagesinfo.Width;
	float sy = height / imagesinfo.Height;



	D3DXMATRIX trans, rotation, scale;
	D3DXMatrixScaling(&scale, sx*scaleX, sy*scaleY, 1);
	D3DXMatrixRotationZ(&rotation, rotate);
	D3DXMatrixTranslation(&trans, x, y, 1.0f);
	pSprite->SetTransform(&(scale * rotation * trans));

	dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->Draw(Texture, &Rect, &center, NULL, color);
	pSprite->Flush();
	dv_font.Sprite->End();

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	pSprite->SetTransform(&identity);
}

void Sprite2::RenderStretch(float x, float y, float width, float height, float scaleX, float scaleY, DWORD color, bool useCam, float rotate, RenderPivot pivot)
{
	if (useCam)
	{
		x += Camera::GetInstance().GetCamX();
		y += Camera::GetInstance().GetCamY();
	}

	ID3DXSprite* pSprite;

	pSprite = dv_font.Sprite;

	//D3DXVECTOR3 position( (float)x, (float)y, 1.0f ) ;

/*	Rect.left   = 0 ;
	Rect.top    = 0 ;
	Rect.right  = Rect.left + imagesinfo.Width ;
	Rect.bottom = Rect.top  + imagesinfo.Height ;
*/
	RECT Rect = { 0, 0, imagesinfo.Width, imagesinfo.Height };									   // sx 0 : 없어짐, 1 : 그대로, 2 : x축으로 2배 확대

	D3DXVECTOR3 center;
	if (pivot == PIVOT_LEFTTOP)
	{
		center.x = 0;
		center.y = 0;
	}
	else if (pivot == PIVOT_CENTER)
	{
		center.x = imagesinfo.Width / 2;
		center.y = imagesinfo.Height / 2;
	}
	center.z = 1;

	float sx = width / imagesinfo.Width;
	float sy = height / imagesinfo.Height;

	//화면 중앙으로
	x += SCREEN_WITH / 2;
	y += SCREEN_HEIGHT / 2;

	//float centerX = (SCREEN_WITH) / 2.0f; // 800은 화면 너비
	//float centerY = (SCREEN_HEIGHT) / 2.0f; // 600은 화면 높이
	//D3DXVECTOR3 centerOfScreen(centerX, centerY, 0);

	D3DXMATRIX trans, rotation, scale;
	D3DXMatrixScaling(&scale, sx * scaleX, sy * scaleY, 1);
	D3DXMatrixRotationZ(&rotation, rotate);
	D3DXMatrixTranslation(&trans, x, y, 1.0f);
	pSprite->SetTransform(&(scale * rotation * trans));

	dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->Draw(Texture, &Rect, &center, NULL, color);
	pSprite->Flush();
	dv_font.Sprite->End();

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	pSprite->SetTransform(&identity);
}
