#include "Include.h"
#include "Cache.h"
#include "ResourceManager.h"
#include "CustomInclude.h"

#define ClipCache AutoDeleteCache<int, AnimationClip>::GetInstance()
#define AnimationCache AutoDeleteCache<int, SpriteAnimation>::GetInstance()
#define AnimatorCache AutoDeleteCache<int, SpriteAnimator>::GetInstance()
#define PlayerDataCache AutoDeleteCache<int, PlayerData>::GetInstance()
#define EnemyDataCache AutoDeleteCache<int, EnemyData>::GetInstance()

ResourceManager::ResourceManager()
	: database(nullptr)
{
}

ResourceManager::~ResourceManager()
{
	if (database != nullptr)
	{
		sqlite3_close(database);
	}
}

void ResourceManager::InitResources()
{	
	if (sqlite3_open("VS_DB.db", &database) != SQLITE_OK)
	{
		MessageBox(nullptr, "데이터베이스 연동 실패!", "치명적 오류", 0);
	}
	//Loading Animators
	LoadAnimator(ID_PLAYER_ANTONIO);
	LoadAnimator(ID_ENEMY_BAT);
	LoadAnimator(ID_ENEMY_MUDMAN);
	//Loading Effects
	LoadAnimation(ID_EFFECT_WHIP);
	//Loading Player Datas
	LoadPlayerData(ID_PLAYER_ANTONIO);
	//Loading Enemy Datas
	LoadEnemyData(ID_ENEMY_BAT);
	LoadEnemyData(ID_ENEMY_MUDMAN);

	sqlite3_close(database);
	database = nullptr;
}

AnimationClip* ResourceManager::LoadClip(int id)
{
	//이미 캐시된 클립이라면 그냥 제공
	AnimationClip* clip = GetClip(id);
	//없으면 DB에서 꺼내오기
	if (clip == nullptr)
	{
		char sql[256] = {};
		sprintf_s(sql, "SELECT * FROM AnimationClip where ID = %d", id);
		sqlite3_stmt* stmt;

		// SQL 문 준비
		if (sqlite3_prepare_v2(database, sql, -1, &stmt, 0) != SQLITE_OK)
		{
			return nullptr;
		}

		if(sqlite3_step(stmt) == SQLITE_ROW)
		{
			clip = new AnimationClip();
			const char* filePath = (const char*)sqlite3_column_text(stmt, 1);
			clip->sprite = new Sprite2();
			clip->sprite->Create(filePath, false);
			clip->hasCollision = sqlite3_column_int(stmt, 2);

			float scale = sqlite3_column_double(stmt, 3);
			clip->SetWH(scale);

			float width = sqlite3_column_double(stmt, 4);
			float height = sqlite3_column_double(stmt, 5);
			clip->width *= width;
			clip->height *= height;
			
			clip->nextAnimDelay = sqlite3_column_double(stmt, 6);

			ClipCache.Put(id, clip);
		}

		sqlite3_finalize(stmt);
	}
	return clip;
}

SpriteAnimation* ResourceManager::LoadAnimation(int id)
{
	SpriteAnimation* anim = GetAnimation(id);
	if (anim == nullptr)
	{
		char sql[256] = {};
		sprintf_s(sql, "SELECT * FROM Animation where ID = %d", id);
		sqlite3_stmt* stmt;

		// SQL 문 준비
		if (sqlite3_prepare_v2(database, sql, -1, &stmt, 0) != SQLITE_OK)
		{
			return nullptr;
		}

		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			char* clipRange = (char*)sqlite3_column_text(stmt, 1);
			
			char* clipBegin = strtok_s(clipRange, "~", &clipRange);
			char* clipEnd = strtok_s(clipRange, "~", &clipRange);

			int begin = atoi(clipBegin);
			int end = begin;
			if (clipEnd != nullptr)
			{
				end = atoi(clipEnd);
			}
			

			bool isLoop = sqlite3_column_int(stmt, 2);

			anim = new SpriteAnimation(isLoop);
			AnimationClip* clip = nullptr;

			for (int i = begin; i <= end; ++i)
			{
				
				if (!ClipCache.Exists(i))
				{
					clip = new AnimationClip(*LoadClip(i));
				}
				else
				{
					clip = GetClip(i);
				}

				anim->Push(clip);
			}
			AnimationCache.Put(id, anim);
		}

		sqlite3_finalize(stmt);
	}
	return anim;
}

SpriteAnimator* ResourceManager::LoadAnimator(int id)
{
	SpriteAnimator* animator = GetAnimator(id);

	if (animator == nullptr)
	{
		char sql[256] = {};
		sprintf_s(sql, "SELECT * FROM Animator where ID = %d", id);
		sqlite3_stmt* stmt;

		// SQL 문 준비
		if (sqlite3_prepare_v2(database, sql, -1, &stmt, 0) != SQLITE_OK)
		{
			return nullptr;
		}


		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			animator = new SpriteAnimator();

			char* situationIDs = (char*)sqlite3_column_text(stmt, 1);
			char* situationID = strtok_s(situationIDs, ",", &situationIDs);

			char* animationIDs = (char*)sqlite3_column_text(stmt, 2);
			char* animationID = strtok_s(animationIDs, ",", &animationIDs);

			SpriteAnimation* animation = nullptr;

			while (situationID != nullptr && animationID != nullptr)
			{
				if (!AnimationCache.Exists(atoi(animationID)))
				{
					animation = new SpriteAnimation(*LoadAnimation(atoi(animationID)));
				}
				else
				{
					animation = GetAnimation(atoi(animationID));
				}

				animator->Insert(atoi(situationID), animation);

				situationID = strtok_s(situationIDs, ",", &situationIDs);
				animationID = strtok_s(animationIDs, ",", &animationIDs);
			}

			AnimatorCache.Put(id, animator);
		}

		sqlite3_finalize(stmt);

	}

	return animator;
}

PlayerData* ResourceManager::LoadPlayerData(int id)
{
	PlayerData* data = GetPlayerData(id);
	if (data == nullptr)
	{
		char sql[256] = {};
		sprintf_s(sql, "SELECT * FROM PlayerData where ID = %d", id);
		sqlite3_stmt* stmt;

		// SQL 문 준비
		if (sqlite3_prepare_v2(database, sql, -1, &stmt, 0) != SQLITE_OK)
		{
			return nullptr;
		}


		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			data = new PlayerData;
			data->animatorID = sqlite3_column_int(stmt, 2);
			data->maxHealth = sqlite3_column_double(stmt, 3);
			data->attackPower = sqlite3_column_double(stmt, 4);
			data->moveSpeed = sqlite3_column_double(stmt, 5);
			data->defense = sqlite3_column_double(stmt, 6);

			PlayerDataCache.Put(id, data);
		}
		sqlite3_finalize(stmt);
	}
	return data;
}

EnemyData* ResourceManager::LoadEnemyData(int id)
{
	EnemyData* data = GetEnemyData(id);
	if (data == nullptr)
	{
		char sql[256] = {};
		sprintf_s(sql, "SELECT * FROM EnemyData where ID = %d", id);
		sqlite3_stmt* stmt;

		// SQL 문 준비
		if (sqlite3_prepare_v2(database, sql, -1, &stmt, 0) != SQLITE_OK)
		{
			return nullptr;
		}


		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			data = new EnemyData;
			data->animatorID = sqlite3_column_int(stmt, 2);
			data->maxHealth = sqlite3_column_double(stmt, 3);
			data->attackPower = sqlite3_column_double(stmt, 4);
			data->moveSpeed = sqlite3_column_double(stmt, 5);

			EnemyDataCache.Put(id, data);
		}
		sqlite3_finalize(stmt);
	}
	return data;
}

AnimationClip* ResourceManager::GetClip(int id)
{
	AnimationClip* clip = ClipCache.Get(id);
	if (clip != nullptr)
		clip = new AnimationClip(*clip);

	return clip;
}

SpriteAnimation* ResourceManager::GetAnimation(int id)
{
	SpriteAnimation* animation = AnimationCache.Get(id);
	if (animation != nullptr)
		animation = new SpriteAnimation(*animation);

	return animation;
}

SpriteAnimator* ResourceManager::GetAnimator(int id)
{
	SpriteAnimator* animator = AnimatorCache.Get(id);
	if (animator != nullptr)
		animator = new SpriteAnimator(*animator);

	return animator;
}

PlayerData* ResourceManager::GetPlayerData(int id)
{
	return PlayerDataCache.Get(id);
}

EnemyData* ResourceManager::GetEnemyData(int id)
{
	return EnemyDataCache.Get(id);
}
