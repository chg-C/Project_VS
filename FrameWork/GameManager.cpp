#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"

static DWORD ALPHATime = GetTickCount64();

GameManager::GameManager(void)
	:map(nullptr), player(nullptr)
{
	GameTime = GetTickCount64();
	m_GameSpeed = 1;
	m_Pause = false;

	m_SysTem.m_Save1 = 100;
	m_SysTem.m_Save2 = 200;
	//Save();

	m_GameStart = true;
	Respawn = false;
}

GameManager::~GameManager(void)
{
	Delete();
}

void GameManager::Init()
{
	map = new Map();
	player = new Player();

	map->Init();
	player->Init();
	
	// ���� ����
	if ((fp = fopen("./Save/save.fss","rb"))== NULL)
	{
		return ;
	}
	
	fread(&m_SysTem,sizeof(SysTem),1,fp);

	fclose(fp);
	
	srand(time(NULL));

	int randomX = 100;
	int randomY = 100;
	int randDirX = 1;
	int randDirY = 1;

	float scale = 1;

	for (int i = 0; i < 100; ++i)
	{
		randDirX = (rand() % 2) == 1 ? 1 : -1;
		randDirY = (rand() % 2) == 1 ? 1 : -1;

		randomX = rand() % 500 + 50;
		randomY = rand() % 500 + 50;

		Enemy* e = new Enemy(randomX * randDirX, randomY * randDirY, scale);
		e->Init();
		enemies.push_back(e);
	}
}

void GameManager::Update()
{
	//if(���� �����) {g_Mng.n_Chap = OVER; Camera::GetInstance().SetCamX(0); Camera::GetInstance().SetCamY(0);}
	map->Update();
	player->Update();
	for (auto& iter : enemies)
	{
		iter->Update();
	}

	//�̵� ó��
	D3DXVECTOR2 velocity = player->GetVelocity();
	player->Move(velocity.x, velocity.y);

	D3DXVECTOR2 playerPos = player->GetPos();
	enemies.sort([playerPos](Enemy* a, Enemy* b) ->
		bool
		{
			float distA =
				abs(a->GetPos().x - playerPos.x)
				+ abs(a->GetPos().y - playerPos.y);
			float distB =
				abs(b->GetPos().x - playerPos.x)
				+ abs(b->GetPos().y - playerPos.y);

			return distA < distB;
		});

	for (auto& iter : enemies)
	{
		velocity = CheckEnemyCollision(iter);
		iter->Move(velocity.x, velocity.y);
	}
}
D3DXVECTOR2 GameManager::CheckEnemyCollision(Enemy* enemy)
{
	D3DXVECTOR2 velocity = enemy->GetVelocity();
	D3DXVECTOR2 direction;

	bool knockback = false;
	
	if (IsColliding(player->GetCollider(0.75f), enemy->GetCollider()))
	{
		//�÷��̾�� ����, ���� �з����� ��
		//�׳� �о������
		direction = enemy->GetPos() - player->GetPos();
		D3DXVec2Normalize(&direction, &direction);
		direction *= 2;
		velocity = direction;
		knockback = true;
	}
	float collisionMP = 1;
	for (auto& iter : enemies)
	{
		if (iter == enemy)
			continue;
		if (IsColliding(enemy->GetCollider(collisionMP), iter->GetCollider(collisionMP)))
		{
			direction = iter->GetPos() - enemy->GetPos();
			//�Ϲ������� �о�� ��				
			D3DXVec2Normalize(&direction, &direction);
			direction *= 2;
			direction.x *= 1 + (rand() % 3 - 1) / 10.f;
			direction.y *= 1 + (rand() % 3 - 1) / 10.f;

			iter->SetVelocity(direction);
		}
	}

	return velocity;
}
bool GameManager::IsColliding(RECT& rectA, RECT& rectB)
{
	return (rectA.left < rectB.right && rectB.left < rectA.right && rectA.top < rectB.bottom && rectB.top < rectA.bottom);
}

void GameManager::Save()
{
	// �ؽ�Ʈ ������ "w" ��
	if ((fp = fopen("./Save/save.fss", "wb")) == NULL)
	{
		return;
	}
	fwrite(&m_SysTem, sizeof(SysTem), 1, fp);
	fclose(fp);

}

void GameManager::Delete()
{
//	sound.g_pSoundManager->drr  
	delete map;
	map = nullptr;

	delete player;
	player = nullptr;

	for (auto& iter : enemies)
	{
		delete iter;
		iter = nullptr;
	}
	enemies.clear();
}
 




void GameManager::GameReset(void)  // ����� ���ӻ� ÷�� �ѹ���  �ʱ�ȭ�Ǵ� �κи� �־���.
{

}


void GameManager::Draw()
{
	D3DXVECTOR2 playerPos = player->GetPos();

	map->Draw();
	for (auto& iter : enemies)
	{
		iter->Draw();
	}
	player->Draw();


	if (m_Pause)
	{
		dv_font.DrawString("ON PAUSE", 420, 300, 0xffff0000);
	}
	else
	{
		dv_font.DrawString("WASD Ȥ�� ����Ű - �̵�", 20, 550, 0xffffffff);
		dv_font.DrawString("SPACEBAR - (�ӽ�)����", 20, 600, 0xffffffff);
	}
}
