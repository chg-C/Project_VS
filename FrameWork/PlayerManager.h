#pragma once

class Player;
class Weapon;

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
private:
	Player* player;
	std::list<Weapon*> weapons;

	Sprite2* squareSprite;

	//Temp Test
	int tmpIdx;
	float keyDelay;
	//

	void DrawInventory();
public:
	void Init(PlayerData* data);
	void Update();
	void Draw();

	bool IsPlaying();

	Player* GetPlayer();
	D3DXVECTOR2 GetPlayerPos();

	const char* GetPlayerName();

	std::list<Weapon*>& GetWeapons();
	void EarnWeapon(WeaponData* data);
};