class g_DeviceFont
{
	int fontHeight;
	int fontWidth;
	int fontWeight;
public:
	IDirect3D9* Direct3D;
	IDirect3DDevice9* Device9;
	D3DPRESENT_PARAMETERS d3dpp ;

	ID3DXSprite* Sprite;       
	ID3DXFont* Fonts;    
	D3DXFONT_DESC fdesc ;

public:
	g_DeviceFont(void);
	~g_DeviceFont(void);

	bool Create(HWND g_hWnd);
	bool DrawString( const char* msg , int x , int y ,int _fontHeight=25,int _fontWidth=12, int fontWeight=500 ,D3DCOLOR color = D3DCOLOR_ARGB( 255,255,255,255) );

};

extern g_DeviceFont dv_font;