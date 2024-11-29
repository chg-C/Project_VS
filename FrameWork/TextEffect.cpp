#include "Include.h"
#include "TextEffect.h"


TextEffect::TextEffect(float x, float y, float scale, const char* texts, float lifeTime)
	: Effect(x, y, scale), texts(nullptr), lifeTime(lifeTime)
{
	this->texts = new char[strlen(texts)];
	strcpy(this->texts, texts);
}

TextEffect::~TextEffect()
{
	//if (texts != nullptr)
	//{
	//	delete[] texts;
	//	texts = nullptr;
	//}
}

void TextEffect::Init()
{

}

void TextEffect::Update()
{
	lifeTime -= TIME;
	if (lifeTime <= 0)
		finished = true;
}

void TextEffect::Draw()
{
	if (!finished)
	{
		float left = Camera::GetInstance().GetCamX() + x + SCREEN_WITH/2;
		float right = left + 16 * strlen(texts);
		float top = Camera::GetInstance().GetCamY() + y + SCREEN_HEIGHT/2;
		float bottom = top + 50;

		RECT rect = { left , top , right, bottom };

		dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , D3DCOLOR_XRGB(255,0,255) ) ;
		//Fonts->DrawText(Sprite, msg, strlen(msg), &rect, DT_NOCLIP, color(원하는 칼러 전달 시));
		dv_font.Fonts->DrawText(dv_font.Sprite, texts, strlen(texts), &rect, DT_NOCLIP, 0xffffffff);
		dv_font.Sprite->End();
	}		
}
