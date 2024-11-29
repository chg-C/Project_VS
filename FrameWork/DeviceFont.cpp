#include "Include.h"

g_DeviceFont dv_font;

g_DeviceFont::g_DeviceFont(void)
{
	// ��Ʈ ���ҽ� �߰�
	AddFontResourceEx("./Typo_SsangmunDongB.ttf", FR_PRIVATE, 0);
}

g_DeviceFont::~g_DeviceFont(void)
{
	Fonts->Release();
}

bool g_DeviceFont::Create( HWND g_hWnd )
{

	Direct3D = Direct3DCreate9( D3D_SDK_VERSION );




	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;												// ��ü ȭ�� ���� ����
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							// ���� ȿ������ SWAP ȿ��
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				            // ���� ����ȭ�� ��忡 ���� �ĸ� ���۸� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ;
	d3dpp.BackBufferWidth = SCREEN_WITH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device9 );


	// ��������Ʈ/��Ʈ �׸��� ���� ����.
	D3DXCreateSprite( Device9 , &Sprite ) ;

	ZeroMemory( &fdesc , sizeof(fdesc) ) ;
	fdesc.Height = fontHeight ;
	fdesc.Width = fontWidth ;
	fdesc.Weight = fontWeight ;
	fdesc.Italic = FALSE ;
	fdesc.CharSet = DEFAULT_CHARSET ;
	//fdesc.FaceName[LF_FACESIZE];
	//strcpy( fdesc.FaceName , "����" ) ;
	strcpy( fdesc.FaceName, "Ÿ����_�ֹ��� B" ) ;

	D3DXCreateFontIndirect( Device9 , &fdesc , &Fonts ) ;

	return true;

}

bool g_DeviceFont::DrawString( const char* msg , int x , int y ,int _fontHeight,int _Width,int _fontWeight, D3DCOLOR color)
{
	//fontHeight = _fontHeight;
	//fontWidth = _Width;
	//fontWeight = _fontWeight;

	//RECT rect = { x , y , fdesc.Width*strlen(msg) , fdesc.Height } ;

	//Sprite->Begin( D3DXSPRITE_ALPHABLEND ) ;
	////Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , D3DCOLOR_XRGB(255,0,255) ) ;
	////Fonts->DrawText(Sprite, msg, strlen(msg), &rect, DT_NOCLIP, color(���ϴ� Į�� ���� ��));
	//Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , color) ;
	//Sprite->End() ;
	//
	//return true;
		// �۲� ���� ����
	fontHeight = _fontHeight;
	fontWidth = _Width;
	fontWeight = _fontWeight;

	// ���� ��Ʈ ��ü ����
	if (Fonts) {
		Fonts->Release();
		Fonts = nullptr;
	}

	// fdesc ����ü ������Ʈ
	ZeroMemory(&fdesc, sizeof(fdesc));
	fdesc.Height = fontHeight;
	fdesc.Width = fontWidth;
	fdesc.Weight = fontWeight;
	fdesc.Italic = FALSE;
	fdesc.CharSet = DEFAULT_CHARSET;
	strcpy(fdesc.FaceName, "Ÿ����_�ֹ��� B");

	// �� �۲� ����
	HRESULT hr = D3DXCreateFontIndirect(Device9, &fdesc, &Fonts);
	if (FAILED(hr)) {
		return false; // �۲� ���� ����
	}

	// ���ڿ� ��� ���� ����
	RECT rect = { x, y, x + 1000, y + fdesc.Height };

	// �ؽ�Ʈ ������
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	Fonts->DrawText(Sprite, msg, -1, &rect, DT_NOCLIP, color);
	Sprite->End();

	return true;
}