#include "Include.h"

g_DeviceFont dv_font;

g_DeviceFont::g_DeviceFont(void)
{
	// 폰트 리소스 추가
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
	d3dpp.Windowed = TRUE;												// 전체 화면 모드로 생성
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							// 가장 효율적인 SWAP 효과
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;				            // 현재 바탕화면 모드에 맞춰 후면 버퍼를 생성
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE ;
	d3dpp.BackBufferWidth = SCREEN_WITH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &Device9 );


	// 스프라이트/폰트 그리기 위해 생성.
	D3DXCreateSprite( Device9 , &Sprite ) ;

	ZeroMemory( &fdesc , sizeof(fdesc) ) ;
	fdesc.Height = fontHeight ;
	fdesc.Width = fontWidth ;
	fdesc.Weight = fontWeight ;
	fdesc.Italic = FALSE ;
	fdesc.CharSet = DEFAULT_CHARSET ;
	//fdesc.FaceName[LF_FACESIZE];
	//strcpy( fdesc.FaceName , "돋움" ) ;
	strcpy( fdesc.FaceName, "타이포_쌍문동 B" ) ;

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
	////Fonts->DrawText(Sprite, msg, strlen(msg), &rect, DT_NOCLIP, color(원하는 칼러 전달 시));
	//Fonts->DrawText( Sprite , msg , strlen( msg ) , &rect , DT_NOCLIP , color) ;
	//Sprite->End() ;
	//
	//return true;
		// 글꼴 설정 변경
	fontHeight = _fontHeight;
	fontWidth = _Width;
	fontWeight = _fontWeight;

	// 기존 폰트 객체 해제
	if (Fonts) {
		Fonts->Release();
		Fonts = nullptr;
	}

	// fdesc 구조체 업데이트
	ZeroMemory(&fdesc, sizeof(fdesc));
	fdesc.Height = fontHeight;
	fdesc.Width = fontWidth;
	fdesc.Weight = fontWeight;
	fdesc.Italic = FALSE;
	fdesc.CharSet = DEFAULT_CHARSET;
	strcpy(fdesc.FaceName, "타이포_쌍문동 B");

	// 새 글꼴 생성
	HRESULT hr = D3DXCreateFontIndirect(Device9, &fdesc, &Fonts);
	if (FAILED(hr)) {
		return false; // 글꼴 생성 실패
	}

	// 문자열 출력 영역 설정
	RECT rect = { x, y, x + 1000, y + fdesc.Height };

	// 텍스트 렌더링
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	Fonts->DrawText(Sprite, msg, -1, &rect, DT_NOCLIP, color);
	Sprite->End();

	return true;
}