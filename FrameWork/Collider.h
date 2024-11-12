#pragma once
#include "Include.h"

class Collider
{


public :
	Collider();
	~Collider();

	RECT m_rc;

	void Init();
	void Update();
	void Draw();

};

extern Collider coll;