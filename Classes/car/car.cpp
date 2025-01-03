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
	std::vector<Zombie*>::iterator it=current_line->begin();   	/*ָ��ʬ����ĵ�����*/
	int size = current_line->size();  /*���ڵõ���vector������*/
	if (!(is_on))       /*δ����С��ʱ�ж���ǰ�潩ʬ��λ���Ƿ񵽴�����λ��*/
	{
		if(size!=0)   /*���ȵ��н�ʬ*/
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
		position = sprite->getPosition();   /*��õ�ǰС��������*/
		if (size != 0) 
		{
			if ((*it)->position.x - position.x < 80)     /*�ж�ʱ��ʬ�϶���С���ұߣ����þ���ֵ*/
			{
				(*it)->blood = -1;
			}
		}
	}
	if (position.x == START_POSITION)  /*�ƶ����յ�λ���˾����ٵ�*/
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
	unscheduleUpdate();    /*�رն�ʱ��*/
	sprite->getParent()->removeChild(sprite);
	delete all_car[line - 1];
}
car::~car()
{
	all_car[line - 1] = NULL;
	Sprite::onExit();
}