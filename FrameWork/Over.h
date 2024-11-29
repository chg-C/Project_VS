#ifndef __Over_H__
#define __Over_H__

class Sprite2;

class Over : public Chap
{
public:
	Over();
	~Over();

	Sprite2* loadimg;

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);
};

#endif