#pragma once
#include "UIPopUp.h"
#include "string"
#include "unordered_map"
enum PowerType
{
	Might,
	MaxHealth,
	Armor,
	Amount,
	Cooldown,
	Area,
	Velocity,
	Duration,
	Speed,
	Magnet,
	Luck,
	Growth,
	TotalSlots,
};

struct PowerSlot:public Slot
{
	std::string name;
	int curLevel;
	int maxLevel;
	int baseCost;
	int increaseCost;
	std::string spritePath;
	UISprite powerSprite;
	UISprite LevelSprite[2];

	PowerSlot(const std::string& name = "", int curLevel = 0, int maxLevel = 0, int baseCost = 0, int increaseCost = 0)
		: name(name), curLevel(curLevel), maxLevel(maxLevel), baseCost(baseCost), increaseCost(increaseCost) {}


	bool Upgrade()
	{
		if (curLevel < maxLevel)
		{
			curLevel++;
			return true;
		}
		else
			return false;
	}
	int CostUpgrade()const
	{
		return baseCost + (increaseCost * curLevel);
	}
};

struct PowerUI
{
	std::vector<UIButton> buttons;
	std::vector<Slot*> slots;
	std::unordered_map<int, std::tuple<int, int, int, int>> UIMap;
};

class PowerPopUp:public UIPopUp
{
	int id;
	int xSpacing;
	int ySpacing;
	int xPos;
	int yPos;

	UIButton backBtn;
	PowerUI ui;

public:
	PowerPopUp();
	~PowerPopUp();
	void RenderElement() override;

	std::unordered_map<int, std::tuple<int, int, int, int>>* GetButtonMap()override;
	std::vector<UIButton>* GetButtons()override;
	std::vector<Slot*>* GetSlots()override;
};

