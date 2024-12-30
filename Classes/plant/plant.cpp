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
	loadResource();          /*������Դ*/
	wait();
}
void Plant::die()
{
	unscheduleUpdate();    /*�رն�ʱ��*/
	sprite->getParent()->removeChild(sprite);
	delete board[line][row];
}
void Plant ::loadResource()
{
	position = sprite->getPosition();
	row = static_cast<int>((position.x - 125) / 85);  /*�̶�λ�÷���ȡֵ�̶ܹ������迼����������*/
	line = static_cast<int>((470 - position.y) / 100);
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

/*����Ϊֲ�����ĺ���*/

BulletShooter::BulletShooter(Sprite* sprite) :Plant(sprite)
{
	interval = 4 * 60;
}
void BulletShooter::shoot()
{
	auto bullet_sprite = Sprite::create("pictures/bullet/pea.png");
	(sprite->getParent())->addChild(bullet_sprite, 3);  /*��sprite�л�ȡ�丸ĸ�����ӵ���ӵ�����Ů��*/
	bullet_sprite->setPosition(Vec2(position.x + 20, position.y + 13));
	bullet* pea = new bullet(bullet_sprite);
	all_bullet.push_back(pea);
}
void BulletShooter::update(float dt)
{
	switch (line)      /*���������õ���Ӧ���ϵĽ�ʬ����*/
	{
	case 0:
		size = line_1.size();
		break;
	case 1:
		size = line_2.size();
		break;
	case 2:
		size = line_3.size();
		break;
	case 3:
		size = line_4.size();
		break;
	case 4:
		size = line_5.size();
		break;
	}
	if (size != 0)       /*��һ����*/
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
	auto s = Sprite::create("pictures/sun.png");
	sun* a = new sun(s);

	all_sun.push_back(a);
	sprite->getParent()->addChild(s, 3);
	s->setPosition(position.x, position.y);     /*�����տ�λ��Ϊ��׼*/
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
	else                     /*������ʼ���ǰ����ʬ*/
	{
		if (!(is_ready))       /*û�л���ɶ�������������*/
		{
			ready();
			is_ready = 1;
		}
		std::vector<zombie*>::iterator it;
		switch (line)
		{
		case 0:
			for (it = line_1.begin(); it < line_1.end(); it++)
			{
				if ((*it)->position.x - position.x < 40 && (*it)->position.x - position.x >= 0)
				{
					(*it)->blood = -1;
					die(); /*������*/
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
					die(); /*������*/
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
					die(); /*������*/
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
					die(); /*������*/
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
					die(); /*������*/
					play_music();
				}
			}
			break;
		}
	}
	if (blood <= 0)
		die();
}
/*����Ϊ����������д����*/
void Plant::setBasic(std::string FrameDir,int wait_num)
{
	this->FrameDir = FrameDir;
	this->wait_num = wait_num;
}
