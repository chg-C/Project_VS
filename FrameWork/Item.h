#pragma once

class Sprite2;

class Item
{
protected:
	Sprite2* icon;
	int id;
public:
	Item();
	virtual ~Item();
};