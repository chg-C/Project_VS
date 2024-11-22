#pragma once
#include "UISprite.h"
#include "UIButton.h"
#include <unordered_map>
#include <vector>
#include "Slot.h"
class UIPopUp:public UISprite 
{
protected:
	bool isOpen;
	UISprite frame;

public:
	UIPopUp();
	~UIPopUp();
	void SetOpen();
	void SetClose();
	void Draw();
	bool GetIsOpen();
	virtual void RenderElement() = 0;
	virtual std::unordered_map<int, std::tuple<int, int, int, int>>* GetButtonMap();
	virtual std::vector<UIButton>* GetButtons();
	virtual std::unordered_map<int, std::tuple<int, int, int, int>>* GetSlotMap();
	virtual std::vector<Slot*>* GetSlots();
};