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

// Chap, ������ �Լ� ȣ��
void Over::Update(double frame)
{
	//if(ó�� ��) g_Mng.n_Chap = MENU; 
	if (KeyDown(VK_RETURN) && GetTickCount64() - key.KeyTime > 1000)
	{
		g_Mng.n_Chap = MENU;
		GameManager::GetInstance().GameReset();
	}
}

void Over::Draw()
{
	
}

void Over::OnMessage( MSG* msg )
{

}