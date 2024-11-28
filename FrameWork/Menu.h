#ifndef __Menu_H__
#define __Menu_H__
#include"UISprite.h"
#include"UIButton.h"
#include"UIPopUp.h"
#include"SelectArrow.h"
#include <unordered_map>
#include"OptionPopUp.h"
#include"PowerPopUp.h"
#include"SoundInterface.h"
struct MenuUI
{
	std::vector<UIButton> menuBtn;
	std::unordered_map<int, std::tuple<int, int, int, int>> buttonMap;//buttonIdx,ÁÂ¿ì»óÇÏ
	MenuUI() {};
};
class Menu : public Chap
{
	int curPopUpIdx;
	int buttonIdx;
	bool isPopUpOpen;
	std::string test[12];

	int testX[4] = {50,80,110,140};
	int testY[3] = { 80,100,120 };

	int xidx;
	int yidx;
	int testidx;

	MenuUI UI;
	UISprite introBG;
	UISprite title;
	UISprite introillust00;
	UISprite introillust01;
	UISprite introillust02;

	UIButton optionBtn;
	UIButton startBtn;
	UIButton collectBtn;
	UIButton powerupBtn;
	UIButton achievementsBtn;
	UIButton creditsBtn;
	SelectArrow selectArrow;

	UIPopUp* curPopUp;
	SoundInterface sound;

public:
	Menu();
	~Menu();

	void AllButtonActivated(bool value);
	int count, alpha;

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();
	virtual void OnMessage(MSG* msg);

	void OpenPopUp(int id);
	void ClosePopUp();
	void MenuInput();
	void OptionInput();
	void PowerInput();

	void HandleKeyInput(int direction);

	void PowerHandle(int direction);
};
#endif