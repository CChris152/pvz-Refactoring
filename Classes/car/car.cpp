#include "PVZ.h"
USING_NS_CC;
car::car(Sprite* outside_sprite,int outside_line)
{
	Sprite::onEnter();
	sprite = outside_sprite;
	line = outside_line;
	switch (line)
	{
	case 1: current_line = &line_1; break;
	case 2: current_line = &line_2; break;
	case 3: current_line = &line_3; break;
	case 4: current_line = &line_4; break;
	case 5: current_line = &line_5; break;
	}
	this->scheduleUpdate();
}
void car::update(float dt)
{
	std::vector<Zombie*>::iterator it=current_line->begin();   	/*指向僵尸数组的迭代器*/
	int size = current_line->size();  /*用于得到当vector的容量*/
	if (!(is_on))       /*未开启小车时判断最前面僵尸的位置是否到达启动位置*/
	{
		if(size!=0)   /*首先得有僵尸*/
		{
			if ((*it)->position.x <= CAR_POSITION+20)
			{
				move();
				is_on = 1;
			}
		}
	}
	else
	{
		position = sprite->getPosition();   /*获得当前小车的坐标*/
		if (size != 0) 
		{
			if ((*it)->position.x - position.x < 80)     /*判定时僵尸肯定在小车右边，不用绝对值*/
			{
				(*it)->blood = -1;
			}
		}
	}
	if (position.x == START_POSITION)  /*移动到终点位置了就销毁掉*/
		die();
}
void car::move()
{
	auto moveby = MoveBy::create(4, Vec2(START_POSITION, 0));
	sprite->runAction(moveby);
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/car.mp3", false, 1.0f, 1.0f, 1.0f);
}
void car::die()
{
	unscheduleUpdate();    /*关闭定时器*/
	sprite->getParent()->removeChild(sprite);
	delete all_car[line - 1];
}
car::~car()
{
	all_car[line - 1] = NULL;
	Sprite::onExit();
}