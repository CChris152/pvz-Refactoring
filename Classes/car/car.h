#pragma once
#include"cocos2d.h"
USING_NS_CC;
class car :public Sprite
{
	int line;
	bool is_on = 0;
	Vec2 position;
	Sprite* sprite;
	std::vector<Zombie*>* current_line = nullptr;
	void move();
	void die();
public:
	car(Sprite* outside_sprite,int outside_line); 
	~car();
	void update(float dt);
};