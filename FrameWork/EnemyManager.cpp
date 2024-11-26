#include "Include.h"

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "TextEffect.h"
#include "Weapon.h"

#include "ResourceManager.h"

EnemyManager::~EnemyManager()
{
	for (auto& iter : enemies)
	{
		SAFE_DELETE(iter);
	}
	enemies.clear();
}

void EnemyManager::Init()
{
	float w = (SCREEN_WITH / 2) * 1.1f;
	float h = (SCREEN_HEIGHT / 2) * 1.1f;

	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i == 0 && j == 0)
				continue;

			EnemySpawnPoint esp;
			
			esp.x = w*i;
			esp.y = h*j;

			esp.cooldown = 5;
			esp.cdRandomRange = 3;

			esp.cooldownRemain = esp.cooldown;
			esp.cooldownRemain += (rand() % (esp.cdRandomRange * 2)) - esp.cdRandomRange;

			spawnPoints.push_back(esp);
		}
	}
}

void EnemyManager::Update()
{
	for (auto& iter = enemies.begin(); iter != enemies.end();)
	{
		(*iter)->Update();
		if ((*iter)->GetState() == CS_DEAD)
		{
			SAFE_DELETE(*iter);
			iter = enemies.erase(iter);

			continue;
		}
		else
		{
			++iter;
		}
	}

	
}

void EnemyManager::Draw()
{
	for (auto& iter : enemies)
	{
		iter->Draw();
	}
}

void EnemyManager::Spawn()
{
	float posX = -Camera::GetInstance().GetCamX();
	float posY = -Camera::GetInstance().GetCamY();
	float randomScale;

	for (auto& iter : spawnPoints)
	{
		iter.cooldownRemain -= TIME;
		if (iter.cooldownRemain <= 0)
		{
			iter.cooldownRemain = iter.cooldown;
			iter.cooldownRemain += (rand() % (iter.cdRandomRange * 2)) - iter.cdRandomRange;

			randomScale = (75 + (rand() % 50)) / 100.0f;

			float r1 = 1 + ((rand() % 250) / 1000.0f);
			float r2 = 1 + ((rand() % 250) / 1000.0f);

			int enemyIdx = ID_ENEMY_BEGIN + 1 + (rand() % 2);

			Enemy* enemy = new Enemy(ResourceManager::GetInstance().GetEnemyData(enemyIdx), posX + (iter.x * r1), posY + (iter.y * r2), randomScale);
			enemy->Init();
			enemies.push_back(enemy);
		}
	}
}

void EnemyManager::Sort(float x, float y)
{
	//�÷��̾���� �Ÿ��� ����� ������� ����
	enemies.sort([x, y](Enemy* a, Enemy* b) ->
		bool
		{
			float distA =
				abs(a->GetPos().x - x)
				+ abs(a->GetPos().y - y);
			float distB =
				abs(b->GetPos().x - x)
				+ abs(b->GetPos().y - y);

			return distA < distB;
		});
}
void EnemyManager::CheckCollision(PlayerManager* player)
{
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 enemyPos;
	D3DXVECTOR2 playerPos = player->GetPlayerPos();
	bool kb = false;
	float knockbackPower = 10;
	char dmgText[6] = "";
	for (auto& iter : enemies)
	{
		enemyPos = iter->GetPos();

		if (Camera::GetInstance().IsOutOfScreen(enemyPos.x, enemyPos.y, 500)) //�÷��� ȭ�� �ٱ����� �ʹ� �ָ� ���ٸ� �ݴ� ��������
		{
			iter->Move(velocity.x, velocity.y);

			float xDist = playerPos.x - enemyPos.x;
			float yDist = playerPos.y - enemyPos.y;

			bool needRev = false;
			if (abs(xDist) > SCREEN_WITH) //�� <-> �� ���� �� ����
			{
				xDist *= -0.6f;
				needRev = true;
			}
			if (abs(yDist) > SCREEN_HEIGHT) //�� <-> �� ���� �� ����
			{
				yDist *= -0.6f;
				needRev = true;
			}

			if (needRev)
			{
				float nX = playerPos.x - xDist;
				float nY = playerPos.y - yDist;

				iter->SetPos(nX, nY);
			}
		}
		else if (iter->IsAlive())
		{
			kb = false;
			//�÷��̾� ���� ����ü�� �浹 üũ
			for (auto& weapon : player->GetWeapons())
			{
				for (auto& proj : weapon->GetProjectiles())
				{
					if (!proj->finished && proj->CanCollide(iter))
					{
						if (IsColliding(proj->GetCollider(), iter->GetCollider()))
						{
							iter->Damage(proj->GetDamage());
							proj->Collide(iter);
							//
							if (Option::GetInstance().WillDamageEffect())
							{
								sprintf_s(dmgText, "%d", (int)proj->GetDamage());
								TextEffect* te = new TextEffect(iter->GetPos().x, iter->GetPos().y, 1, dmgText, 0.5f);
								GameManager::GetInstance().RegisterEffect(te);
							}
							//
							kb = true;

							velocity.x = iter->GetPos().x - playerPos.x;
							velocity.y = iter->GetPos().y - playerPos.y;
							D3DXVec2Normalize(&velocity, &velocity);
							velocity *= knockbackPower;
						}
					}
				}
			}
			//�˹����� �ƴ϶�� ĳ���� �� �浹 üũ
			if (!kb)
			{
				velocity = CheckEnemyCollision(player->GetPlayer(), iter);
			}
			//���������� �̵� ó��
			iter->Move(velocity.x, velocity.y);
		}
	}
}
D3DXVECTOR2 EnemyManager::CheckEnemyCollision(Player* player, Enemy* enemy)
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
		velocity = direction;

		knockback = true;
		//player->Hit()
		player->Damage(enemy->GetDamage());
	}
	float collisionMP = 1;
	float distanceX, distanceY;
	float overlapX, overlapY;
	for (auto& iter : enemies)
	{
		if (iter == enemy || !iter->IsAlive())
			continue;
	
		if (IsColliding(enemy->GetCollider(collisionMP), iter->GetCollider(collisionMP)))
		{
			direction = iter->GetPos() - enemy->GetPos();

			// x��� y���� �Ÿ� ���
			distanceX = abs(direction.x);
			distanceY = abs(direction.y);
	
			// �� ���� ��ġ�� ���� ���
			overlapX = (iter->GetSize().x + enemy->GetSize().x) / 2.0f - distanceX;
			overlapY = (iter->GetSize().y + enemy->GetSize().y) / 2.0f - distanceY;
	
			// ��ħ�� ���� ��� ó��
			if (overlapX > 0 && overlapY > 0) {
				// �� ���� ��ħ ������ ��
				if (overlapX < overlapY) {
					// x������ �и�
					if (direction.x > 0) {
						iter->Move(overlapX, 0);
						enemy->Move(-overlapX, 0);
					}
					else {
						iter->Move(-overlapX, 0);
						enemy->Move(overlapX, 0);
					}
				}
				else {
					// y������ �и�
					if (direction.y > 0) {
						iter->Move(0, overlapY);
						enemy->Move(0, -overlapY);
					}
					else {
						iter->Move(0, -overlapY);
						enemy->Move(0, overlapY);
					}
				}
			}
		}
	}
	
	return velocity;
}
//D3DXVECTOR2 EnemyManager::CheckEnemyCollision(Enemy* enemy)
//{

//}
