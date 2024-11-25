#pragma once

class Sprite2;

class Item
{
	Sprite2* icon;
	int id;
public:
	Item();
	virtual ~Item();
};