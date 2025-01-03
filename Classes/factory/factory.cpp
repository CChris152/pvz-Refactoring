#include "PVZ.h"
USING_NS_CC;
Sprite* Factory::add_sprite(cocos2d::Node* parent,int layer)
{
	auto sprite = Sprite::create();
	parent->addChild(sprite, layer);
	return sprite;
}

/*工厂基类函数*/
Zombie* ZombieFactory::add_zombie(double line, cocos2d::Node* parent)
{
	auto sprite = Factory::add_sprite(parent, 3);
	sprite->setPosition(Vec2(START_POSITION, line));
	Zombie* normal = new Zombie(sprite, line);
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
void ZombieFactory::load_normal(Zombie * zombie)
{
	zombie->setBasic("pictures/zombie/normal/", 60, 1200, 0,21,22);
	zombie->loadResource();
}
void ZombieFactory::load_flag(Zombie* zombie)
{
	zombie->setBasic("pictures/zombie/Flag/", 20, 1200, 1, 11,12 );
	zombie->loadResource();
}
void ZombieFactory::load_buckethead(Zombie* zombie)
{
	zombie->setBasic("pictures/zombie/Buckethead/", 60, 3600, 2, 11, 15);
	zombie->loadResource();
}


/*僵尸工厂函数*/


Sprite *  PlantFactory::add_plant(int row,int line,cocos2d::Node* parent)
{
	auto sprite = add_sprite(parent, 2);
	sprite->setPosition(row * 85 + 125, 470 - line * 100);
	return sprite;
	Plant*  plant= new Plant(sprite);
	plant->setBasic("pictures/plant/bullet_shooter/", 13);


	plant->loadResource();
	board[line][row] = plant;
	return plant;
}
void PlantFactory::load(int row,int line,Plant* plant)
{
	plant->loadResource();
	board[line][row] = plant;
}
void PlantFactory::add_bulletShooter(int row, int line, cocos2d::Node* parent)
{
	auto sprite = add_plant(row, line, parent);
	BulletShooter* shooter = new BulletShooter(sprite);
	shooter->setBasic("pictures/plant/bullet_shooter/", 13);
	load(row, line,shooter);
}
void PlantFactory::add_sunflower(int row, int line, cocos2d::Node* parent)
{
	auto sprite = add_plant(row, line, parent);
	Sunflower* sunflower = new Sunflower(sprite);
	sunflower->setBasic("pictures/plant/sunflower/", 18);
	load(row, line, sunflower);
}
void PlantFactory::add_nut(int row, int line, cocos2d::Node* parent)
{
	auto sprite = add_plant(row, line, parent);
	Nut* nut = new Nut(sprite);
	nut->setBasic("pictures/plant/nut/", 8);
	load(row, line, nut);
}
void PlantFactory::add_potatoMine(int row, int line, cocos2d::Node* parent)
{
	auto sprite = add_plant(row, line, parent);
	PotatoMine* mine = new PotatoMine(sprite);
	mine->setBasic("pictures/plant/potato_mine/", 8);
	load(row, line, mine);
}

