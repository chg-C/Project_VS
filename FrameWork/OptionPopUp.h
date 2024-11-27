#pragma once
#include <vector>
#include <unordered_map>
#include"UIPopUp.h"
#include"UIButton.h"

struct OptionUI
{
	std::vector<UIButton> optionButton;
	std::unordered_map<int, std::tuple<int, int, int, int>> UIMap;//buttonIndex, {аб,©Л,╩С,го}
	OptionUI() {};;
};

class OptionPopUp:public UIPopUp
{
	int id;
	OptionUI UI;
	UIButton backBtn;
	UIButton soundBtn;
	UIButton musicBtn;
	UIButton damageNumbersBtn;

public:
	OptionPopUp();
	~OptionPopUp();
	void Init();
	void RenderElement() override;
	std::unordered_map<int, std::tuple<int, int, int, int>>* GetButtonMap() override;

	std::vector<UIButton>* GetButtons() override;

};