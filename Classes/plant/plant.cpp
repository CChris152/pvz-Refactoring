#include "PVZ.h"
USING_NS_CC;
Plant::Plant(Sprite*outside_sprite)
{
	Sprite::onEnter();
	sprite = outside_sprite;
	this->scheduleUpdate();
}
Plant::~Plant()
{
	board[line][row] = NULL;
	Sprite::onExit();
}
void Plant::plant_init()
{
	loadResource();          /*加载资源*/
	wait();
}
void Plant::die()
{
	unscheduleUpdate();    /*关闭定时器*/
	sprite->getParent()->removeChild(sprite);
	delete board[line][row];
}
void Plant ::loadResource()
{
	position = sprite->getPosition();
	row = static_cast<int>((position.x - 125) / 85);  /*固定位置放置取值很固定，无需考虑四舍五入*/
	line = static_cast<int>((470 - position.y) / 100);
	switch (line)
	{
	case 0: current_line = &line_1; break;
	case 1: current_line = &line_2; break;
	case 2: current_line = &line_3; break;
	case 3: current_line = &line_4; break;
	case 4: current_line = &line_5; break;
	}
	init_wait_animate();
	wait();
}
void Plant::wait()
{
	is_wait = true;
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(waitFrames, 1.0 / 15))));;
}
void Plant::init_wait_animate()
{
	for (int i = 1; i < wait_num + 1; i++)
	{
		std::string num = std::to_string(i);
		waitFrames.pushBack(SpriteFrame::create(FrameDir+num+".png", Rect(0, 0, 75, 75)));
	}
}

/*以上为植物基类的函数*/

BulletShooter::BulletShooter(Sprite* sprite) :Plant(sprite)
{
	interval = 4 * 60;
}
void BulletShooter::shoot()
{
	auto bullet = new Bullet(sprite->getParent());
	bullet->load(Vec2(position.x + 20, position.y + 13));
	all_bullet.push_back(bullet);
}
void BulletShooter::update(float dt)
{
	size = current_line->size();
	if (size != 0)       /*这一行上*/
		interval--;
	if (interval == 0)
	{
		shoot();
		interval = BULLET_SHOOT;
	}
	if (blood <= 0)
	{
		die();
	}
}
Sunflower::Sunflower(Sprite* sprite):Plant(sprite)
{
	interval = 15 * 60;
}
void Sunflower::create_sun()
{
	sun* a = nullptr;
	for (sun* tmp : sunPool) //从池中获取对象
	{
		if (tmp->getState() == false)
		{
			a = tmp;
			a->setBusy();
			break;
		}
	}
	if (a == nullptr)
	{
		auto s = Sprite::create("pictures/sun.png");
		a = new sun(s);
		sprite->getParent()->addChild(s, 3);
		sunPool.push_back(a);
	}
	else
	{
		a->sprite->setOpacity(255);
		a->init_listener();
		a->scheduleUpdate();
	}

	a->sprite->setPosition(position.x, position.y);     /*以向日葵位置为基准*/
	a->create();
}
void Sunflower::update(float dt)
{
	interval--;
	if (interval == 0)
	{
		create_sun();
		interval = SUNFLOWER_CREATE;
	}
	if (blood <= 0)
	{
		die();
	}
}
Nut::Nut(Sprite* sprite) :Plant(sprite)
{
	interval = 0;
	blood = 5000;
}
void Nut::update(float dt)
{
	if (blood <= 0)
	{
		die();
	}
}
PotatoMine::PotatoMine(Sprite* sprite) :Plant(sprite)
{
	blood = 500;
	interval = 5 * 60;
}
void PotatoMine::ready()
{
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(waitFrames, 1.0 / 15))));;
}
void PotatoMine::wait()
{
	sprite->stopAllActions();
	sprite->setTexture("pictures/plant/potato_mine/wait.png");
}
void PotatoMine::play_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/potato_mine.mp3", false);
}
void PotatoMine::update(float dt)
{
	if (interval != 0)
		interval--;
	else                     /*启动后开始检测前方僵尸*/
	{
		if (!(is_ready))       /*没切换完成动画就启动动画*/
		{
			ready();
			is_ready = 1;
		}
		std::vector<Zombie*>::iterator it;
		switch (line)
		{
		case 0:
			for (it = line_1.begin(); it < line_1.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*销毁了*/
					play_music();
				}
			}
			break;
		case 1:
			for (it = line_2.begin(); it < line_2.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*销毁了*/
					play_music();
				}
			}
			break;
		case 2:
			for (it = line_3.begin(); it < line_3.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*销毁了*/
					play_music();
				}
			}
			break;
		case 3:
			for (it = line_4.begin(); it < line_4.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*销毁了*/
					play_music();
				}
			}
			break;
		case 4:
			for (it = line_5.begin(); it < line_5.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*销毁了*/
					play_music();
				}
			}
			break;
		}
	}
	if (blood <= 0)
		die();
}
/*以上为土地雷所重写函数*/
void Plant::setBasic(std::string FrameDir,int wait_num)
{
	this->FrameDir = FrameDir;
	this->wait_num = wait_num;
}
