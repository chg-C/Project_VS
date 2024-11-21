#pragma once
#include "Include.h"
#include "Singleton.h"
#include <map>
#include <functional>
#include <vector>
class UIManager:public Singleton<UIManager>
{
	friend class Singleton<UIManager>;
public:
	UIManager() {}
	~UIManager() {}
private:
	int popupCount=0;
	std::map<int, UIPopUp*> popupMap;
	std::vector<UIButton> buttons;
	std::unordered_map<int, std::tuple<int, int, int, int>> buttonMap;//buttonIndex, {аб,©Л,╩С,го}
public:
	void Init()
	{
		new OptionPopUp;
		new PowerPopUp;
	}

	void RegisterPopUp(int id, UIPopUp* popUp)
	{
		popupMap[id] = popUp;
		popupCount++;
	}

	void OpenPopUp(int id)
	{
		popupMap[id]->SetOpen();
	}
	void ClosePopUp(int id)
	{
		popupMap[id]->SetClose();
	}
	UIPopUp* GetPopUp(int id)
	{
		return popupMap[id];
	}
	int GetPopUPCount()
	{
		return popupCount;
	}

	std::vector<UIButton>& GetButtons() {
		return buttons;
	}

	void SetButtons(const std::vector<UIButton>& newButtons) {
		buttons = newButtons;
	}

	std::unordered_map<int, std::tuple<int, int, int, int>>& GetButtonMap() {
		return buttonMap;
	}

	void SetButtonMap(const std::unordered_map<int, std::tuple<int, int, int, int>>& newButtonMap) {
		buttonMap = newButtonMap;
	}

};