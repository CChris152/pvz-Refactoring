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
	line = static_cast<int>((600-outside_line)/100);
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
	for (int i = 1; i < move_num + 1; i++)
	{
		std::string num = std::to_string(i);
		moveFrames.pushBack(SpriteFrame::create(FrameDir+"move/"+num+".png", Rect(0, 0, 166, 144)));
	}
}
void zombie::init_eat_animate()
{
	for (int i = 1; i < eat_num + 1; i++)
	{
		std::string num = std::to_string(i);
		eatFrames.pushBack(SpriteFrame::create(FrameDir + "eat/" + num + ".png", Rect(0, 0, 166, 144)));
	}
}
void zombie::init_wait_animate()
{
	for (int i = 1; i < 11 + 1; i++)
	{
		std::string num = std::to_string(i);
		waitFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/wait/" + num + ".png", Rect(0, 0, 166, 144)));
	}
}
void zombie::init_die_animate()
{
	for (int i = 1; i < 20+1; i++)
	{
		std::string num = std::to_string(i);
		dieFrames.pushBack(SpriteFrame::create("pictures/zombie/normal/die/" + num + ".png", Rect(0, 0, 166, 144)));
	}
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

/*Refectoring*/
void zombie::setBasic(std::string FrameDir, int speed, double blood, int type,int eat_num,int move_num)
{
	this->FrameDir = FrameDir;
	this->speed = speed;
	this->type = type;
	this->blood = blood;
	this->eat_num = eat_num;
	this->move_num = move_num;
}