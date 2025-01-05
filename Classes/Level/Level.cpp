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
template <typename T>
void Level::off_schedule(std::vector<T*>& vec) {
	for (auto it = vec.begin(); it != vec.end(); it++) {
		if (*it != nullptr) {
			(*it)->unscheduleUpdate();
			delete (*it);
		}
	}
	vec.clear();
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
	off_schedule(sunPool);
}
void Level::off_zombie_schedule()
{
	off_schedule(line_1);
	off_schedule(line_2);
	off_schedule(line_3);
	off_schedule(line_4);
	off_schedule(line_5);
}
void Level::off_bullet_schedule()
{
	off_schedule(all_bullet);
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
	visibleSize = Director::getInstance()->getVisibleSize(); /*��ȡ���ڴ�С*/
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
	addlabel();
	addshovel();
	addmusic();

}
void Level::addbackground()
{
	auto background = Sprite::create("pictures/icon/level_1.jpg");          /*����ͼƬ����*/
	background->setPosition(Vec2(530, 295));
	addChild(background, 0);      /*�������²�*/
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
	auto shop = Sprite::create("pictures/icon/shop.png");                  /*�̵�ͼƬ*/
	shop->setPosition(Vec2(300, 550));
	addChild(shop, 1);
}
void Level::addcard()
{
	bulletShooterCard.card_init(this, new BulletShooterCardBehavior());
	sunflowerCard.card_init(this, new SunflowerCardBehavior());
	nutCard.card_init(this, new NutCardBehavior());
	potatoMineCard.card_init(this, new PotatoMineCardBehavior());
}
void Level::addcar()
{
	for (int i = 0; i < 5; i++)
	{
		auto sprite = Sprite::create("pictures/car.png");
		this->addChild(sprite, 3);
		sprite->setPosition(Vec2(CAR_POSITION, 470 - 100 * i));
		car *a=new car(sprite, i + 1);
		all_car[i] = a;     /*�洢�����鵱��*/
	}
}
void Level::addloadingBar()
{
	auto Bar = Sprite::create("pictures/icon/loadingBar.png");   /*������*/
	Bar->setPosition(Vec2(820, 10));
	this->addChild(Bar, 3);


	auto head = Sprite::create("pictures/icon/time.png");    /*��ʾʱ���õ�С��ʬͷ*/
	head->setPosition(Vec2(880, 10));
	this->addChild(head, 5);

	auto moveBy = MoveBy::create(135, Vec2(-120, 0));    
	/*��Ϊ��ʼ��ʱִ�ж����������������ֱ��ʹ����ʱ��/60(����ĵ�λ���룬ͷ�ļ���time�ĵ�λ��֡)���ƶ�*/
	head->runAction(moveBy);

	auto flag = Sprite::create("pictures/icon/flag.png");    /*��ʾ�����õ�����*/
	flag->setPosition(Vec2(760, 15));
	this->addChild(flag, 4);

}
void Level::addmusic()
{
	/*���ñ�������*/
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/gaming.mp3", true);  /*����Ϊtrue���ظ�����*/
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
		Vec2 pt = t->getLocation();  /*�õ���ǰ����*/
		shovel->setPosition(pt);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, shovel);
}
bool Level::touch_shovel_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*�õ���ǰ����*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*ȡ�õ�ǰ����Ķ���*/
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

void Level::addexitButton()      /*����˳���ť*/
{
	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/exit.png",
		Vec2(800, 550),
		[this]() {
			back_to_select();
		});
}
/*�ɵ��������Ӧ��������*/
void Level::back_to_select()
{
	stop_music();
	auto scene = select::createScene();
	Director::getInstance()->replaceScene(scene);
}
void Level::addzombie()
{
	int line = rand() % 5+1;   /*����������Ϊ[1,5]*/
	ZombieFactory::add_normal_zombie(static_cast<double>(570 - line * 100), this);
	        /*���������Ƕ������ȶ���������һ����ʬ*/
}
void Level::update(float dt)
{
	sun_total->setString(StringUtils::format("%d", total));   /*ˢ��̫������*/
	time++;
	if (current_state)
	{
		current_state->handle(this);
	}
}

void Level::stop()
{
	stop_plant();
	stop_zombie();
	stop_music();
	stop_bullet();
	this->unscheduleUpdate();   /*�Ѷ�ʱ�����˷�ֹ�����������*/
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
				board[i][j]->unscheduleUpdate();   /*�Ѷ�ʱ�����ˣ���ֹ���������ӵ�*/
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
/*����Ϊ�ؿ��������ú���*/

Scene* Level_1::createScene()
{
	return Level_1::create();
}
void Level_1::addcard()
{
	bulletShooterCard.card_init(this, new BulletShooterCardBehavior());
	sunflowerCard.card_init(this, new SunflowerCardBehavior());
	/*�㶹���ֿ�Ƭ���*/

	/*���տ���Ƭ���*/
	addcar();
}
void Level_1::set_level_ready()
{
	level_1_ready = 1;
    UserDefault::getInstance()->setBoolForKey("level_1_ready", 1);
}
/*����Ϊ�ؿ�һ����д����ʵ��*/
Scene* Level_2::createScene()
{
	return Level_2::create();
}
void Level_2::addcard()
{
	bulletShooterCard.card_init(this, new BulletShooterCardBehavior());
	sunflowerCard.card_init(this, new SunflowerCardBehavior());
	nutCard.card_init(this, new NutCardBehavior());
	addcar();
}
void Level_2::set_level_ready()
{
	level_2_ready = 1;
	UserDefault::getInstance()->setBoolForKey("level_2_ready", 1);
}
/*����Ϊ�ؿ�������д����ʵ��*/

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