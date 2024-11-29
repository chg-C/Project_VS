#include "Include.h"

Over::Over()
{
}

Over::~Over()
{
}

void Over::Init()
{

}

// Chap, 재정의 함수 호출
void Over::Update(double frame)
{
	//if(처리 후) g_Mng.n_Chap = MENU; 
	if (KeyDown(VK_RETURN) && GetTickCount64() - key.KeyTime > 1000)
	{
		GameManager::GetInstance().GameReset();
		g_Mng.SwitchChapter(MENU);
	}
}

void Over::Draw()
{
	
}

void Over::OnMessage( MSG* msg )
{

}