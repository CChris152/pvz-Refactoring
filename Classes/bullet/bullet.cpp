#include"HelloWorldScene.h"
USING_NS_CC;
bullet::bullet(Sprite* outside_sprite)
{
	Sprite::onEnter();
	sprite = outside_sprite;
	position = sprite->getPosition();
	bullet::get_line();
	bullet::move();
	scheduleUpdate();
}
bullet::~bullet()
{
	Sprite::onExit();
}
void bullet::update(float dt)
{
	position = sprite->getPosition();
	bullet::is_zombie();
}
void bullet::hit_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/bullet_hit.mp3", false, 1.0f, 1.0f, 1.0f);
}

void bullet::hit_Buckethead_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/shieldhit.mp3", false, 1.0f, 1.0f, 1.0f);
}
void bullet::get_line()
{
	int i =static_cast<int>((570 - position.y+13) / 100);
	/*加13是因为子弹的位置会比初始位置高13，这样才能和豌豆射手的嘴水平*/
	line = i;
}
/*获得子弹所在的行*/
void bullet::is_zombie()
{
	std::vector<zombie*>::iterator it;  /*用迭代器遍历对应的vector容器中的僵尸坐标，若小于一定范围就判定为击中目标*/
	switch (line)
	{
	case 1:
		for (it = line_1.begin(); it < line_1.end(); it++)
		{
			if (position.x - (*it)->position.x < 20&& position.x - (*it)->position.x > 0)
			{
				if ((*it)->type == 2)
					hit_Buckethead_music();
				else
					hit_music();
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);      /*将子弹移除*/
				unscheduleUpdate();
				break;
			}
		}
		break;
	case 2:
		for (it = line_2.begin(); it < line_2.end(); it++)
		{
			if (position.x - (*it)->position.x < 20 && position.x - (*it)->position.x > 0)
			{
				if ((*it)->type == 2)
					hit_Buckethead_music();
				else
					hit_music();
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);      /*将子弹移除*/
				unscheduleUpdate();
				break;
			}
		}
		break;
	case 3:
		for (it = line_3.begin(); it < line_3.end(); it++)
		{
			if (position.x - (*it)->position.x < 20 && position.x - (*it)->position.x > 0)
			{
				if ((*it)->type == 2)
					hit_Buckethead_music();
				else
					hit_music();
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);      /*将子弹移除*/
				unscheduleUpdate();
				break;
			}
		}
		break;
	case 4:
		for (it = line_4.begin(); it < line_4.end(); it++)
		{
			if (position.x - (*it)->position.x < 20 && position.x - (*it)->position.x > 0)
			{
				if ((*it)->type == 2)
					hit_Buckethead_music();
				else
					hit_music();
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);      /*将子弹移除*/
				unscheduleUpdate();
				break;
			}
		}
		break;
	case 5:
		for (it = line_5.begin(); it < line_5.end(); it++)
		{
			if (position.x - (*it)->position.x < 20 && position.x - (*it)->position.x > 0)
			{
				if ((*it)->type == 2)
					hit_Buckethead_music();
				else
					hit_music();
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);      /*将子弹移除*/
				unscheduleUpdate();
				break;
			}
		}
		break;
	}
}
/*判断是否碰撞到僵尸*/
void bullet::move()
{
	auto moveby = MoveBy::create(4, Vec2(START_POSITION, 0));
	sprite->runAction(moveby);
}
/*进行移动*/