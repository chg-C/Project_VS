class CMng
{
public:
	CMng();
	~CMng();


	///////////////////////// ��������Ʈ ��ü! ///////////////////
//	Sprite loadimg;  // �ΰ��̹���

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