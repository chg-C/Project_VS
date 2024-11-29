#include "Include.h"
CMng g_Mng;

CMng::CMng()
{
	n_Chap = LOGO;
	
}

CMng::~CMng()
{
}

void CMng::SwitchChapter(int id)
{
	n_Chap = id;
	GetCurrentChapter()->OnSwitched();
}
