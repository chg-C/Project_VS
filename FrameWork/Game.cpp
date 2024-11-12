#include "Include.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	map.Init();
	bird.Init();
	player.Init();
	coll.Init();
	sound.Init();
	Gmanager.Init();
	// ����Ÿ ���̽�///////////////////
	sql.Init();
}

void Game::Draw()
{
	map.Draw();
	bird.Draw();
	player.Draw();
	coll.Draw();
	Gmanager.Draw();
	// ����Ÿ ���̽�///////////////////
	sql.Draw();
}

// Chap, ������ �Լ� ȣ��
void Game::Update(double frame)
{
	//static int a = 0;
	//if(a == 0) 
	//{
	//	GameTime = GetTickCount();
	//	a = 1;
	//}
	static DWORD a = 0;

	if (GetTickCount64() - a > frame)
	{
		key.Update();
		bird.Update();
		player.Update();
		coll.Update();
		// �� ���� �°�
		map.Update(130);
		Gmanager.Update();
		// ����Ÿ ���̽�///////////////////
		// �� ���� �°� (���⼱ �Ⱦ���..������ ���� �ʿ� �Ҷ���.. �׳� �����...)
		sql.Update(frame+3000);

		a = GetTickCount64();
	}
	

}


void Game::OnMessage( MSG* msg )
{

}