#include "PVZ.h"
USING_NS_CC;

void ReadyState::handle(Level* level)
{
	if (level->getTime() > READY_DURATION)
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("Music/zombie_comming.mp3", false);   /*单次播放*/
		level->setState(new GamingState());
	}
}
void GamingState::handle(Level* level)
{
	if (judge_fail())
		level->setState(new FailState());
	sun_interval--;
	if (sun_interval == 0) // 间隔性生成阳光
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
				zombie_interval = ZOMBIE_CREATE;  /*重置一下数字*/
			else
				zombie_interval = 1 * 60;
		}
	}
	else
		level->setState(new FlushState());

}
bool GamingState::judge_fail()
{
	/*因为没有安排速度更快的僵尸，所以每一行vector的第一个元素一定是位置最前的僵尸，只需检测0位置的僵尸位置即可*/
	std::vector<Zombie*>::iterator it;
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
		level->addChild(s, 5);
		sunPool.push_back(a);
	}
	else
	{
		a->sprite->setOpacity(255);
		a->init_listener();
		a->scheduleUpdate();
	}
	int x = 70 + rand() % 735;
	a->sprite->setPosition(x, SUN_START);
	a->fall();
}
void FlushState::handle(Level* level)
{
	if (flush_time != 0) {
		if (flush_time % 100 == 0) {
			int tmp_line = rand() % 5 + 1; // 随机选择行
			int line = tmp_line - 1; // 将行号转换为索引

			if (flush_time == 3000) { // 生成特殊僵尸
				ZombieFactory::add_flag_zombie(470-line*100, level);
			}
			// 使用数组来存储每行的计数器
			int* num_array[] = { &num_1, &num_2, &num_3, &num_4, &num_5 };
			if (*num_array[line] <= 6) { // 检查是否达到上限
				(*num_array[line])++;
				if (Buckethead_num != 0) { // 检查是否有桶头僵尸
					ZombieFactory::add_buckethead_zombie(470 - line * 100, level);
					Buckethead_num--;
				}
				else {
					ZombieFactory::add_normal_zombie(470 - line * 100, level);
				}
			}
		}
		flush_time--;
	}
	else if (line_1.empty() && line_2.empty() && line_3.empty() && line_4.empty() && line_5.empty()) {
		// 检查是否所有行都没有僵尸
		level->setState(new WinState());
	}

}
void FailState::handle(Level* level)
{
	level->stop();
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/losemusic.mp3", false);
	/*失败音乐播放*/

	auto sprite = Sprite::create("pictures/icon/fail.png");
	level->addChild(sprite, 5);
	sprite->setPosition(Vec2(400, 350));
	auto label = Label::createWithTTF("PRESS TO BACK THE MENU", "fonts/Marker Felt.ttf", 50);
	label->setTextColor(Color4B::BLACK);
	label->setPosition(400, 100);
	level->addChild(label, 5);
	/*失败图标创建*/

	auto listener = EventListenerTouchOneByOne::create();
	/*创建监听器*/
	listener->onTouchBegan = [&](Touch* t, Event* e)    /*随便点击就退出*/
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
		auto audio = SimpleAudioEngine::getInstance();   /*胜利音乐播放*/
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
		/*获胜图标创建*/
	}
	else if (win_time != 0)     /*纪录播放时间，播放完了再切换到选关界面*/
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