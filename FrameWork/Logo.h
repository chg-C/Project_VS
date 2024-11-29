#ifndef __Logo_H__
#define __Logo_H__


class Sprite2;

class Logo : public Chap
{
public:
	Logo();
	~Logo();

	//CSound* Sound1;
	Sprite2* loadimg;
	Sprite2* loadimg2;

	Sprite2* square;

	float speed;
	float alpha;

	char loadingText[256];

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();

	virtual void OnMessage(MSG* msg);

	
};

#endif