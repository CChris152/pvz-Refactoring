#include "PVZ.h"
USING_NS_CC;

void ReadyState::handle(Level* level)
{
	if (level->getTime() > READY_DURATION)
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("Music/zombie_comming.mp3", false);   /*���β���*/
		level->setState(new GamingState());
	}
}
void GamingState::handle(Level* level)
{
	if (judge_fail())
		level->setState(new FailState());
	sun_interval--;
	if (sun_interval == 0) // �������������
	{
		sun_interval = SUN_CREATE;
		add_sun(level);
	}
	if (level->getTime() < FLUSH_DURATION)
	{
		zombie_interval--;
		if (zombie_interval == 0)
		{
			int num = rand() % 101;
			if (num > per)
				num = 1;
			else
				num = 2;
			level->addzombie();
			if (num == 1)
				zombie_interval = ZOMBIE_CREATE;  /*����һ������*/
			else
				zombie_interval = 1 * 60;
		}
	}
	else
		level->setState(new FlushState());

}
bool GamingState::judge_fail()
{
	/*��Ϊû�а����ٶȸ���Ľ�ʬ������ÿһ��vector�ĵ�һ��Ԫ��һ����λ����ǰ�Ľ�ʬ��ֻ����0λ�õĽ�ʬλ�ü���*/
	std::vector<zombie*>::iterator it;
	it = line_1.begin();
	if (line_1.size() != 0)
	{
		if ((*it)->position.x <= END_POSITION)
			return true;
	}
	it = line_2.begin();
	if (line_2.size() != 0)
	{
		if ((*it)->position.x <= END_POSITION)
			return true;
	}
	it = line_3.begin();
	if (line_3.size() != 0)
	{
		if ((*it)->position.x <= END_POSITION)
			return true;
	}
	it = line_4.begin();
	if (line_4.size() != 0)
	{
		if ((*it)->position.x <= END_POSITION)
			return true;
	}
	it = line_5.begin();
	if (line_5.size() != 0)
	{
		if ((*it)->position.x <= END_POSITION)
			return true;
	}
	return false;
}
void GamingState::add_sun(Level* level)
{
	auto s = Sprite::create("pictures/sun.png");
	sun* a = new sun(s);
	all_sun.push_back(a);
	level->addChild(s, 5);
	int x = 70 + rand() % 735;   /*�������ɺ�λ����[70,805)*/
	s->setPosition(x, SUN_START);
	a->fall();   /*ִ�е���*/
}
void FlushState::handle(Level* level)
{
	if (flush_time != 0)
	{
		if (flush_time % 100 == 0)
		{
			int tmp_line = rand() % 5 + 1; /*�����������������ʬ*/
			switch (tmp_line)
			{
			case 1:
				if (flush_time == 2000)   /*�������Ľ�ʬ*/
				{
					ZombieFactory::add_flag_zombie(LINE_1, level);
				}
				if (num_1 <= 6)
				{                 /*��ÿһ�з��䵽�Ľ�ʬ������ƽ��һ��*/
					num_1++;
					if (Buckethead_num != 0)     /*�����ͨ��ʬ*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_1, level);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_1, level);
				}
				break;
			case 2:
				if (flush_time == 2000)   /*�������Ľ�ʬ*/
				{
					ZombieFactory::add_flag_zombie(LINE_2, level);
				}
				if (num_2 <= 6)
				{                 /*��ÿһ�з��䵽�Ľ�ʬ������ƽ��һ��*/
					num_2++;
					if (Buckethead_num != 0)     /*�����ͨ��ʬ*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_2, level);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_2, level);
				}
				break;
			case 3:
				if (flush_time == 2000)   /*�������Ľ�ʬ*/
				{
					ZombieFactory::add_flag_zombie(LINE_3, level);
				}
				if (num_3 <= 6)
				{                 /*��ÿһ�з��䵽�Ľ�ʬ������ƽ��һ��*/
					num_3++;
					if (Buckethead_num != 0)     /*�����ͨ��ʬ*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_3, level);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_3, level);
				}
				break;
			case 4:
				if (flush_time == 2000)   /*�������Ľ�ʬ*/
				{
					ZombieFactory::add_flag_zombie(LINE_4, level);
				}
				if (num_4 <= 6)
				{                 /*��ÿһ�з��䵽�Ľ�ʬ������ƽ��һ��*/
					num_4++;
					if (Buckethead_num != 0)     /*�����ͨ��ʬ*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_4, level);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_4, level);
				}
				break;
			case 5:
				if (flush_time == 2000)   /*�������Ľ�ʬ*/
				{
					ZombieFactory::add_flag_zombie(LINE_5, level);
				}
				if (num_5 <= 6)
				{                 /*��ÿһ�з��䵽�Ľ�ʬ������ƽ��һ��*/
					num_5++;
					if (Buckethead_num != 0)     /*�����ͨ��ʬ*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_5, level);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_5, level);
				}
				break;
			}
		}
		flush_time--;
	}
	else if(line_1.size()==0
		&& line_2.size() == 0
		&& line_3.size() == 0
		&& line_4.size() == 0
		&& line_5.size() == 0)/*�����һ��ִ��֮����ҵ�ǰ��ʬ��ɱ����ж�Ϊ��Ϸʤ��*/
		level->setState(new WinState());
}
void FailState::handle(Level* level)
{
	level->stop();
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/losemusic.mp3", false);
	/*ʧ�����ֲ���*/

	auto sprite = Sprite::create("pictures/icon/fail.png");
	level->addChild(sprite, 5);
	sprite->setPosition(Vec2(400, 350));
	auto label = Label::createWithTTF("PRESS TO BACK THE MENU", "fonts/Marker Felt.ttf", 50);
	label->setTextColor(Color4B::BLACK);
	label->setPosition(400, 100);
	level->addChild(label, 5);
	/*ʧ��ͼ�괴��*/

	auto listener = EventListenerTouchOneByOne::create();
	/*����������*/
	listener->onTouchBegan = [&](Touch* t, Event* e)    /*��������˳�*/
	{
		level->back_to_select();
		return true;
	};
	level->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
	
}


void WinState::handle(Level* level)
{
	level->set_level_ready();
	if (!(is_play))
	{
		auto audio = SimpleAudioEngine::getInstance();   /*ʤ�����ֲ���*/
		audio->stopAllEffects();
		audio->playEffect("Music/winmusic.mp3", false);
		is_play = 1;

		auto label = Label::createWithTTF("You Win!!!", "fonts/Marker Felt.ttf", 80);
		label->setTextColor(Color4B::BLACK);
		label->setPosition(400, 300);
		level->addChild(label, 5);
		auto label2 = Label::createWithTTF("You have a new plant in next level", "fonts/Marker Felt.ttf", 60);
		label2->setTextColor(Color4B::BLACK);
		label2->setPosition(400, 100);
		level->addChild(label2, 5);
		/*��ʤͼ�괴��*/
	}
	else if (win_time != 0)     /*��¼����ʱ�䣬�����������л���ѡ�ؽ���*/
		win_time--;
	else
		back_to_select();
}
void WinState::back_to_select()
{
	stop_music();
	auto scene = select::createScene();
	Director::getInstance()->replaceScene(scene);
}
void WinState::stop_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopAllEffects();
}