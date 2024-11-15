#ifndef __Menu_H__
#define __Menu_H__
#include"UISprite.h"
#include"UIButton.h"
#include"SelectArrow.h"
class Menu : public Chap
{
	int buttonIdx;
	UISprite introBG;
	UISprite introillust00;
	UISprite introillust01;
	UISprite introillust02;
	UIButton startBtn;
	UIButton collectBtn;
	UIButton achievementsBtn;
	SelectArrow selectArrow;

	std::vector<UIButton> menuBtn;
public:
	Menu();
	~Menu();


	int count, alpha;


	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

};

#endif