#pragma once

class Player;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
private:
	Player* player;
	std::list<Projectile*> projectiles;

	SpriteAnimation* attackEffectTemplate;
public:
	void Init(PlayerData* data);
	void Update();
	void Draw();

	bool IsPlaying();

	Player* GetPlayer();
	D3DXVECTOR2 GetPlayerPos();

	std::list<Projectile*>& GetProjectiles();
};