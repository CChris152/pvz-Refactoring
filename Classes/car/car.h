#pragma once
#include"cocos2d.h"
USING_NS_CC;
class car :public Sprite
{
	int line;
	bool is_on = 0;
	Vec2 position;
	Sprite* sprite;
public:
	car(Sprite* outside_sprite,int outside_line); 
	~car();
	void judge_punch(int line);
	void die();
	void update(float dt);
	void move();
};