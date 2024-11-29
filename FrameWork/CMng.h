class CMng
{
public:
	CMng();
	~CMng();


	///////////////////////// 스프라이트 객체! ///////////////////
//	Sprite loadimg;  // 로고이미지

	//////////////////////////////////////////////////////////////


	HWND hWnd;
	HINSTANCE hInstance;

	Chap *chap[TOTALCHAP];
public:
	void SwitchChapter(int id);
	Chap* GetCurrentChapter() { return chap[n_Chap]; }
private:
	int n_Chap;
};

extern CMng g_Mng;