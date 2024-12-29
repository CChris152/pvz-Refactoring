#include "PVZ.h"
USING_NS_CC;
Sprite* Factory::add_sprite(cocos2d::Node* parent,int layer)
{
	auto sprite = Sprite::create();
	parent->addChild(sprite, layer);
	return sprite;
}
zombie* ZombieFactory::add_zombie(double line, cocos2d::Node* parent)
{
	auto sprite = Factory::add_sprite(parent, 3);
	sprite->setPosition(Vec2(START_POSITION, line));
	zombie* normal = new zombie(sprite, line);
	int i = static_cast<int>((600 - line) / 100);
	switch (i)
	{
	case 1:
		line_1.push_back(normal);
		break;
	case 2:
		line_2.push_back(normal);
		break;
	case 3:
		line_3.push_back(normal);
		break;
	case 4:
		line_4.push_back(normal);
		break;
	case 5:
		line_5.push_back(normal);
		break;
	}
	return normal;
}
void ZombieFactory::add_normal_zombie(double line, cocos2d::Node* parent)
{
	load_normal(add_zombie(line, parent));
}
void ZombieFactory::add_flag_zombie(double line, cocos2d::Node* parent)
{
	load_flag(add_zombie(line, parent));
}
void ZombieFactory::add_buckethead_zombie(double line, cocos2d::Node* parent)
{
	load_buckethead(add_zombie(line, parent));
}
void ZombieFactory::load_normal(zombie * zombie)
{
	zombie->setBasic("pictures/zombie/normal/", 60, 1200, 0,21,22);
	zombie->loadResource();
}
void ZombieFactory::load_flag(zombie* zombie)
{
	zombie->setBasic("pictures/zombie/Flag/", 20, 1200, 1, 11,12 );
	zombie->loadResource();
}
void ZombieFactory::load_buckethead(zombie* zombie)
{
	zombie->setBasic("pictures/zombie/Buckethead/", 60, 3600, 2, 11, 15);
	zombie->loadResource();
}