#include "PVZ.h"
USING_NS_CC;
Level::~Level()
{
	this->off_zombie_schedule();
	this->off_plant_schedule();
	this->off_bullet_schedule();
	this->off_sun();
	this->off_car();
	this->removeAllChildren();
	this->unscheduleUpdate();
	line_1.clear();
	line_2.clear();
	line_3.clear();
	line_4.clear();
	line_5.clear();
	sunPool.clear();
	all_bullet.clear();
	total = 0;

}
void Level::off_car()
{
	for (int i=0; i<5; i++)
	{
		if (all_car[i] != NULL)
		{
			delete all_car[i];
		}
	}
}
void Level::off_sun()
{
	std::vector<sun*>::iterator it;
	for (it = sunPool.begin(); it != sunPool.end(); it++)
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
}
void Level::off_zombie_schedule()
{
	std::vector<Zombie*>::iterator it;
	for (it = line_1.begin(); it != line_1.end(); it++)   /*关闭所有的定时器，并删除分配好的内存*/
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
	for (it = line_2.begin(); it != line_2.end(); it++)   /*关闭所有的定时器，并删除分配好的内存*/
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
	for (it = line_3.begin(); it != line_3.end(); it++)   /*关闭所有的定时器，并删除分配好的内存*/
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
	for (it = line_4.begin(); it != line_4.end(); it++)   /*关闭所有的定时器，并删除分配好的内存*/
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
	for (it = line_5.begin(); it != line_5.end(); it++)   /*关闭所有的定时器，并删除分配好的内存*/
	{
		(*it)->unscheduleUpdate();
		delete (*it);
	}
}
void Level::off_bullet_schedule()
{

}
void Level::off_plant_schedule()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j]!=NULL)
			{
				delete board[i][j];
			}
		}
	}
}

Scene* Level::createScene()  
{
	return Level::create();
}
bool Level::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize(); /*获取窗口大小*/
	loadResoure();
	this->scheduleUpdate();
	setState(new ReadyState());
	return true;
}
void Level::loadResoure()
{
	addbackground();
	addshop();
	addcard();
	addloadingBar();
	addexitButton();
	/*	addstopButton();*/
	addlabel();
	addshovel();
	addmusic();
}
void Level::addbackground()
{
	auto background = Sprite::create("pictures/icon/level_1.jpg");          /*背景图片设置*/
	background->setPosition(Vec2(530, 295));
	addChild(background, 0);      /*放在最下层*/
}
void Level::addlabel()
{
	sun_total = Label::createWithTTF(StringUtils::format("%d",total), "fonts/arial.ttf",20);
	sun_total->setTextColor(Color4B::BLACK);
	sun_total->setPosition(113, 515);
	this->addChild(sun_total, 5);
}
void Level::addshop()
{
	auto shop = Sprite::create("pictures/icon/shop.png");                  /*商店图片*/
	shop->setPosition(Vec2(300, 550));
	addChild(shop, 1);
}
void Level::addcard()
{

	/*
	bullet_shooter_card.sprite = Sprite::create("pictures/card/bullets_shooter.png");
	addChild(bullet_shooter_card.sprite, 2);
	bullet_shooter_card.card_init();
	*/
	/*豌豆射手卡片添加*/

	/*
		Sunflower_Card.sprite = Sprite::create("pictures/card/sunflower.png");
	addChild(Sunflower_Card.sprite, 2);
	Sunflower_Card.card_init();
	*/

	/*向日葵卡片添加*/

	/*
		Nut_Card.sprite = Sprite::create("pictures/card/nut.png");
	addChild(Nut_Card.sprite, 2);
	Nut_Card.card_init();
	*/

	/*坚果墙卡片添加*/

	/*
		Potato_Mine_Card.sprite = Sprite::create("pictures/card/potato_mine.png");
	addChild(Potato_Mine_Card.sprite, 2);
	Potato_Mine_Card.card_init();
	*/

	/*土地雷卡片添加*/
}
void Level::addcar()
{
	for (int i = 0; i < 5; i++)
	{
		auto sprite = Sprite::create("pictures/car.png");
		this->addChild(sprite, 3);
		sprite->setPosition(Vec2(CAR_POSITION, 470 - 100 * i));
		car *a=new car(sprite, i + 1);
		all_car[i] = a;     /*存储到数组当中*/
	}
}
void Level::addloadingBar()
{
	auto Bar = Sprite::create("pictures/icon/loadingBar.png");   /*进度条*/
	Bar->setPosition(Vec2(820, 10));
	this->addChild(Bar, 3);


	auto head = Sprite::create("pictures/icon/time.png");    /*显示时间用的小僵尸头*/
	head->setPosition(Vec2(880, 10));
	this->addChild(head, 5);

	auto moveBy = MoveBy::create(FLUSH_DURATION/60, Vec2(-120, 0));   
	/*因为初始化时执行动作，所以这里可以直接使用总时间/60(这里的单位是秒，头文件里time的单位是帧)来移动*/
	head->runAction(moveBy);

	auto flag = Sprite::create("pictures/icon/flag.png");    /*显示波次用的旗子*/
	flag->setPosition(Vec2(760, 15));
	this->addChild(flag, 4);

}
void Level::addmusic()
{
	/*设置背景音乐*/
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/gaming.mp3", true);  /*设置为true，重复播放*/
}


void Level::addshovel()
{
	shovel = Sprite::create("pictures/icon/shovel.png");
	this->addChild(shovel, 4);
	shovel->setPosition(Vec2(500, 550));
	init_shovel();
}
void Level::init_shovel()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Level::touch_shovel_began, this);
	listener->onTouchEnded = CC_CALLBACK_2(Level::touch_shovel_end, this);
	listener->onTouchMoved = [&](Touch* t, Event* e)
	{
		Vec2 pt = t->getLocation();  /*得到当前坐标*/
		shovel->setPosition(pt);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, shovel);
}
bool Level::touch_shovel_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		return true;
	}
	return false;
}
bool Level::is_in_board(Vec2 pt)
{
	auto checkLine = [&](int block) {
		return fabs(pt.x - block) < 20 &&
			(fabs(pt.y - LINE_1) < 20 || fabs(pt.y - LINE_2) < 20 ||
				fabs(pt.y - LINE_3) < 20 || fabs(pt.y - LINE_4) < 20 ||
				fabs(pt.y - LINE_5) < 20);
		};

	return checkLine(BLOCK_1) || checkLine(BLOCK_2) || checkLine(BLOCK_3) ||
		checkLine(BLOCK_4) || checkLine(BLOCK_5) || checkLine(BLOCK_6) ||
		checkLine(BLOCK_7) || checkLine(BLOCK_8) || checkLine(BLOCK_9);
}
bool Level::is_empty(Vec2 pt)
{
	int row = static_cast<int>((pt.x - 125 + 50) / 85);
	int line = static_cast<int>((fabs(600 - pt.y)) / 100) - 1;
	return (row >= 0 && row < 9 && line >= 0 && line < 5 && board[line][row] == NULL);
}
bool Level::touch_shovel_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		if (is_in_board(pt))
		{
			if (!(is_empty(pt)))
			{
				int row = static_cast<int>((fabs(pt.x - 75)) / 85);
				int line = static_cast<int>((fabs(650 - pt.y)) / 100) - 1;
				board[line][row]->blood = 0;
			}
		}
		shovel->setPosition(Vec2(500, 550));
		return true;
	}
	return false;
}

void Level::addexitButton()      /*添加退出按钮*/
{
	exitButton = Sprite::create("pictures/icon/exit.png");
	exitButton->setPosition(Vec2(800, 550));
	addChild(exitButton, 1);
	init_exitButton_event();
}
void Level::init_exitButton_event()      /*创建退出监听器*/
{
	auto exitListener = EventListenerTouchOneByOne::create();
	exitListener->onTouchBegan = CC_CALLBACK_2(Level::touch_exitButton_began, this);
	exitListener->onTouchEnded = CC_CALLBACK_2(Level::touch_exitButton_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(exitListener, exitButton);
}
bool Level::touch_exitButton_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		sprite->setTexture("pictures/icon/exit_select.png"); /*将图片变为选择状态*/
		return true;
	}
	return false;
}
bool Level::touch_exitButton_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
		back_to_select();
		return true;
	}
	sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
	return false;
}

/*可点击精灵相应函数如上*/
/*以上为调试工具*/
void Level::back_to_select()
{
	stop_music();
	auto scene = select::createScene();
	Director::getInstance()->replaceScene(scene);
}
void Level::addzombie()
{
	int line = rand() % 5+1;   /*产生的行数为[1,5]*/
	ZombieFactory::add_normal_zombie(static_cast<double>(570 - line * 100), this);
	        /*无论数量是多少首先都得先生成一个僵尸*/
}
void Level::update(float dt)
{
	sun_total->setString(StringUtils::format("%d", total));   /*刷新太阳总数*/
	time++;
	if (current_state)
	{
		current_state->handle(this);
	}
}
void Level::flush()
{

}
void Level::stop()
{
	stop_plant();
	stop_zombie();
	stop_music();
	stop_bullet();
	this->unscheduleUpdate();   /*把定时器关了防止阳光继续生成*/
}
void Level::stop_plant()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board[i][j] != NULL)
			{
				board[i][j]->sprite->stopAllActions();
				board[i][j]->unscheduleUpdate();   /*把定时器关了，防止继续产生子弹*/
			}
		}
	}
}
void Level::stop_bullet()
{
	std::vector<Bullet*>::iterator it;
	for (it = all_bullet.begin(); it != all_bullet.end(); it++)
	{
		(*it)->unscheduleUpdate();
	}
}
void Level::stop_zombie()
{
	std::vector<Zombie*>::iterator it;
	for (it = line_1.begin(); it != line_1.end(); it++)   
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
	for (it = line_2.begin(); it != line_2.end(); it++)  
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
	for (it = line_3.begin(); it != line_3.end(); it++)   
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
	for (it = line_4.begin(); it != line_4.end(); it++)  
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
	for (it = line_5.begin(); it != line_5.end(); it++)  
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
}
void Level::stop_sun()
{
	std::vector<sun*>::iterator it;
	for (it = sunPool.begin(); it != sunPool.end(); it++)
	{
		(*it)->unscheduleUpdate();
		(*it)->sprite->stopAllActions();
	}
}
void Level::stop_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopAllEffects();
}
/*以上为关卡基类所用函数*/

Scene* Level_1::createScene()
{
	return Level_1::create();
}
void Level_1::addcard()
{
	per = 60;
	flush_time = 1000;
	Buckethead_num = 0;

	bulletShooterCard.card_init(this, new BulletShooterCardBehavior());
	sunflowerCard.card_init(this, new SunflowerCardBehavior());
	/*豌豆射手卡片添加*/

    
	/*向日葵卡片添加*/
	addcar();
}
void Level_1::flush()
{
	if (flush_time != 0)
	{
		if (flush_time % 100 == 0)
		{
			int tmp_line = rand() % 5 + 1; /*在五行里随机产生僵尸*/
			switch (tmp_line)
			{
			case 1:
				if (flush_time == 1000)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_1, this);
				}
				if (num_1 <= 2)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_1++;
					ZombieFactory::add_normal_zombie(LINE_1, this);
				}
				break;
			case 2:
				if (flush_time == 1000)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_2, this);
				}
				if (num_2 <= 2)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_2++;
					ZombieFactory::add_normal_zombie(LINE_2, this);
				}
				break;
			case 3:
				if (flush_time == 1000)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_3, this);
				}
				if (num_3 <= 2)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_3++;
					ZombieFactory::add_normal_zombie(LINE_3, this);
				}
				break;
			case 4:
				if (flush_time == 1000)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_4, this);
				}
				if (num_4 <= 2)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_4++;
					ZombieFactory::add_normal_zombie(LINE_4, this);
				}
				break;
			case 5:
				if (flush_time == 1000)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_5, this);
				}
				if (num_5 <= 2)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_5++;
					ZombieFactory::add_normal_zombie(LINE_5, this);
				}
				break;
			}
		}
		flush_time--;
	}
	else
		is_flush = 1;    /*设置为已完全释放该波次*/
}
void Level_1::set_level_ready()
{
	level_1_ready = 1;
    UserDefault::getInstance()->setBoolForKey("level_1_ready", 1);
}
/*以上为关卡一的重写函数实现*/
Scene* Level_2::createScene()
{
	return Level_2::create();
}
void Level_2::addcard()
{
	bulletShooterCard.card_init(this, new BulletShooterCardBehavior());
	sunflowerCard.card_init(this, new SunflowerCardBehavior());
	
	addcar();
}
void Level_2::flush()
{
	if (flush_time != 0)
	{
		if (flush_time % 100 == 0)
		{
			int tmp_line = rand() % 5 + 1; /*在五行里随机产生僵尸*/
			switch (tmp_line)
			{
			case 1:
				if (flush_time == 1500)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_1, this);
				}
				if (num_1 <= 4)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_1++;
					if (Buckethead_num != 0)     /*添加铁通僵尸*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_1, this);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_1, this);
				}
				break;
			case 2:
				if (flush_time == 1500)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_2, this);
				}
				if (num_2 <= 4)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_2++;
					if (Buckethead_num != 0)     /*添加铁通僵尸*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_2, this);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_2, this);
				}
				break;
			case 3:
				if (flush_time == 1500)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_3, this);
				}
				if (num_3 <= 4)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_3++;
					if (Buckethead_num != 0)     /*添加铁通僵尸*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_3, this);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_3, this);
				}
				break;
			case 4:
				if (flush_time == 1500)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_4, this);
				}
				if (num_4 <= 4)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_4++;
					if (Buckethead_num != 0)     /*添加铁通僵尸*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_4, this);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_4, this);
				}
				break;
			case 5:
				if (flush_time == 1500)   /*生成旗帜僵尸*/
				{
					ZombieFactory::add_flag_zombie(LINE_5, this);
				}
				if (num_5 <= 4)
				{                 /*让每一行分配到的僵尸数量都平均一点*/
					num_5++;
					if (Buckethead_num != 0)     /*添加铁通僵尸*/
					{
						ZombieFactory::add_buckethead_zombie(LINE_5, this);
						Buckethead_num--;
					}
					else
						ZombieFactory::add_normal_zombie(LINE_5, this);
				}
				break;
			}
		}
		flush_time--;
	}
	else
		is_flush = 1;    /*设置为已完全释放该波次*/
}
void Level_2::set_level_ready()
{
	level_2_ready = 1;
	UserDefault::getInstance()->setBoolForKey("level_2_ready", 1);
}
/*以上为关卡二的重写函数实现*/

/*refectoring*/
void Level::setState(LevelState* state)
{
	delete current_state;
	current_state = state;
	
}

int Level::getTime()
{
	return time;
}