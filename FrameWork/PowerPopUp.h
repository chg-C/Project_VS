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

struct Slot
{
	std::string name;
	int curLevel;
	int maxLevel;
	int baseCost;
	int increaseCost;

	bool isSelected;

	UISprite slotSprite;
	UISprite powerSprite;


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
	std::unordered_map<int, std::tuple<int, int, int, int>> UImap;
	Slot slots[TotalSlots];
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
};