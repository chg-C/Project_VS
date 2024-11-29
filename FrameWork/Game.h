#ifndef __Game_H__
#define __Game_H__
#include "UIPopUp.h"

class Game : public Chap
{
	bool wasReturnPressed = false;
	int uiIdx;
	SoundInterface sound;
	UIPopUp* curPopUp;
public:
	Game();
	~Game();

	DWORD GameTime;
	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);
	virtual void OnSwitched();

	void HandleKeyInput(int direction);
	void OptionInput();
};

#endif