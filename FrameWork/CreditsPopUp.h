#pragma once
#include <vector>
#include <unordered_map>
#include"UIPopUp.h"
#include"UIButton.h"
struct UI
{
	std::vector<UIButton> Buttons;
	std::unordered_map<int, std::tuple<int, int, int, int>> UIMap;//buttonIndex, {аб,©Л,╩С,го}
};
class CreditsPopUp :public UIPopUp
{
	int id;
	UIButton backBtn;
	UI ui;
public:
	CreditsPopUp();
	~CreditsPopUp();
	void Init()override;
	void RenderElement() override;
	std::unordered_map<int, std::tuple<int, int, int, int>>* GetButtonMap() override;

	std::vector<UIButton>* GetButtons() override;
};