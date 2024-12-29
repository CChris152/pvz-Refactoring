#include "PVZ.h"
USING_NS_CC;
zombie::~zombie()
{
	Sprite::onExit();
}
zombie::zombie(Sprite *outside_sprite,double outside_line)
{
	Sprite::onEnter();
	sprite = outside_sprite;
	speed = 60;
	line = static_cast<int>((600-outside_line)/100);
	type = 0;               /*普通僵尸标识*/
	loadResource();          /*加载资源*/
	this->scheduleUpdate();
}
void zombie::loadResource()
{
	position = sprite->getPosition();
	init_animate();
	move();
}
void zombie::eatmusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->setEffectsVolume(0.2);
	eat_music=audio->playEffect("Music/eat.mp3", true, 1.0f, 1.0f, 1.0f);
}
void zombie::update(float dt)
{
	position = sprite->getPosition();     /*获取当前坐标位置*/
	row = static_cast<int>((position.x - 125) / 85);
	if (blood <= 0)
	{
		if (!(is_die))  /*还没有执行死亡动画*/
		{
			stopmusic();
			sprite->stopAllActions();      /*停止动画*/
			sprite->runAction(Animate::create(Animation::createWithSpriteFrames(dieFrames, 1.0 / 12)));
			is_die = 1;
		}
		else
			die_time--;
		if(die_time==0)/*动画执行完毕*/
		    die();
	}
	if (row >= 0)   /*走到方格外就不检测了，不然会越界*/
	{
		judge_eat();
	}

}
void zombie::die()
{
	unscheduleUpdate();    /*关闭定时器*/
	sprite->getParent()->removeChild(sprite);
	switch (line)     /*将对应的数组元素清理*/
	{
	case 1:
		delete line_1[0];
		line_1.erase(line_1.begin(), line_1.begin() + 1);
		break;
	case 2:
		delete line_2[0];
		line_2.erase(line_2.begin(), line_2.begin() + 1);
		break;
	case 3:
		delete line_3[0];
		line_3.erase(line_3.begin(), line_3.begin() + 1);
		break;
	case 4:
		delete line_4[0];
		line_4.erase(line_4.begin(), line_4.begin() + 1);
		break;
	case 5:
		delete line_5[0];
		line_5.erase(line_5.begin(), line_5.begin() + 1);
		break;
	}
}
void zombie::eat()
{
	is_eat = true;
	is_wait = false;
	is_move = false;
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(eatFrames, 1.0/10))));;
}
void zombie::move()
{
	is_eat = false;
	is_wait = false;
	is_move = true;
	sprite->stopAllActions();
	sprite->runAction(MoveBy::create(speed, Vec2(-START_POSITION, 0)));
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(moveFrames, 1.0 / 8)
		)));
}
void zombie::wait()
{
	is_eat = false;
	is_wait = true;
	is_move = false;
	sprite->stopAllActions();
	sprite->runAction(RepeatForever::create(
		Animate::create(Animation::createWithSpriteFrames(waitFrames, 1.0 / 15))));;
}
void zombie::init_animate()
{
	init_move_animate();
	init_eat_animate();
	init_wait_animate();
	init_die_animate();
}
void zombie::init_move_animate()
{
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/1.png",Rect(0,0,166,144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/2.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/3.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/4.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/5.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/6.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/7.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/8.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/9.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/10.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/11.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/12.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/13.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/14.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/15.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/16.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/17.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/18.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/19.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/20.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/21.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/move/22.png", Rect(0, 0, 166, 144)));
}
void zombie::init_eat_animate()
{
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/1.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/2.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/3.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/4.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/5.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/6.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/7.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/8.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/9.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/10.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/11.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/12.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/13.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/14.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/15.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/16.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/17.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/18.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/19.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/20.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/eat/21.png", Rect(0, 0, 166, 144)));
}
void zombie::init_wait_animate()
{
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/1.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/2.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/3.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/4.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/5.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/6.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/7.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/8.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/9.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/10.png", Rect(0, 0, 166, 144)));
	waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/11.png", Rect(0, 0, 166, 144)));
}
void zombie::init_die_animate()
{
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/1.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/2.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/3.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/4.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/5.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/6.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/7.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/8.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/9.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/10.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/11.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/12.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/13.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/14.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/15.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/16.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/17.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/18.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/19.png", Rect(0, 0, 166, 144)));
	dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/20.png", Rect(0, 0, 166, 144)));
}
bool zombie::judge_eat()
{
	int i = line-1;
	static int k;
	if (board[i][row] != nullptr)
	{
		if (position.x - board[i][row]->position.x < 20 && position.x - board[i][row]->position.x > 0)   /*检测到前面有植物，开始吃*/
		{
			if (is_eat)  /*如果开始吃了*/
			{
				k--;
				if (k == 0)
				{
					k = interval;
					board[i][row]->blood -= attack;
				}
				return true;
			}
			else
			{
				eat();
				eatmusic();
				k = interval;
				return true;
			}
		}
		else
		{
			stopmusic();
			if (k != interval)
				k = interval;
			if (!(is_move))
				move();
		}
	}
	if (!(is_move))
	{
		move();
		stopmusic();
	}
	return false;    /*一行都遍历完毕还没有遇到植物，则返回false*/
}
void zombie::stopmusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopEffect(eat_music);
}

/*以上为僵尸基类的函数实现*/
flag_zombie::flag_zombie(Sprite* outside_sprite, double outside_line) :zombie(outside_sprite, outside_line)
{
	speed = 20;         /*设置速度*/
	type = 1;          /*旗帜僵尸标识*/
	init_animate();
	move();
}
void flag_zombie::init_eat_animate()
{
	eatFrames.clear();
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/1.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/2.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/3.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/4.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/5.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/6.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/7.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/8.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/9.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/10.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/eat/11.png", Rect(0, 0, 166, 144)));
}
void flag_zombie::init_move_animate()
{
	moveFrames.clear();
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/1.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/2.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/3.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/4.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/5.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/6.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/7.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/8.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/9.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/10.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/11.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Flag/move/12.png", Rect(0, 0, 166, 144)));
}
/*以上为旗帜僵尸函数实现*/

Buckethead_zombie::Buckethead_zombie(Sprite* outside_sprite, double outside_line):zombie(outside_sprite, outside_line)
{
	blood = 3600;      /*设置血量*/
	type = 2;            /*铁通僵尸标识*/
	init_animate();
	move();
}
void Buckethead_zombie::init_eat_animate()
{
	eatFrames.clear();
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/1.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/2.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/3.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/4.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/5.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/6.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/7.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/8.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/9.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/10.png", Rect(0, 0, 166, 144)));
	eatFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/eat/11.png", Rect(0, 0, 166, 144)));
}
void Buckethead_zombie::init_move_animate()
{
	moveFrames.clear();
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/1.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/2.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/3.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/4.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/5.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/6.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/7.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/8.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/9.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/10.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/11.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/12.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/13.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/14.png", Rect(0, 0, 166, 144)));
	moveFrames.pushBack(SpriteFrame::create("pictures/zombie/Buckethead/move/15.png", Rect(0, 0, 166, 144)));
}