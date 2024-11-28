#ifndef __Game_H__
#define __Game_H__

#include"SoundInterface.h"
class Game : public Chap
{
public:
	Game();
	~Game();

	DWORD GameTime;
	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

	virtual void OnSwitched();
private:
	SoundInterface sound;
};

#endif