#include "include.h"
#include "UISprite.h"

UISprite::UISprite()
{
}

UISprite::~UISprite()
{
}



void UISprite::UIRender(float x, float y, float radian, float sx, float sy,int pivotMode, DWORD setColor)
{
    RECT Rect;                                                           // sx 0 : 없어짐, 1 : 그대로, 2 : x축으로 2배 확대
    ID3DXSprite* pSprite;                                                // pivotMode 0: Left Top, 1: Center Mid

    pSprite = dv_font.Sprite;

    Rect.left = 0;
    Rect.top = 0;
    Rect.right = Rect.left + imagesinfo.Width;
    Rect.bottom = Rect.top + imagesinfo.Height;
    
    D3DXVECTOR3 center;
    if (pivotMode == 0)
    {
        center.x = 0.0f;
        center.y = 0.0f;
    }
    else if (pivotMode == 1)
    {
        center.x = imagesinfo.Width / 2.0f;
        center.y = imagesinfo.Height / 2.0f;
    }
    center.z = 1.0f;

    float sizeX = sx / imagesinfo.Width;
    float sizeY = sy / imagesinfo.Height;
    D3DXMATRIX rot, trans, scale;
    D3DXMatrixScaling(&scale, sizeX, sizeY, 1);
    D3DXMatrixRotationZ(&rot, radian);
    D3DXMatrixTranslation(&trans, x, y, 1.0f);
    pSprite->SetTransform(&(scale * rot * trans));

    dv_font.Sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pSprite->Draw(Texture, &Rect, &center, NULL, setColor);
    pSprite->Flush();
    dv_font.Sprite->End();

    D3DXMATRIX identity;
    D3DXMatrixIdentity(&identity);
    pSprite->SetTransform(&identity);
}
