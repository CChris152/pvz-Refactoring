#include "HelloWorldScene.h"
USING_NS_CC;
select::~select()
{
	this->removeAllChildren();
}
Scene* select::createScene()
{
	return select::create();
}
bool select::init()
{
	if (!Scene::init())
	{
		return false;
	}
	loadResource();
	return true;
}
void select::loadResource()
{
	add_background();
	add_music();
	add_Level_1();
	add_Level_2();
	add_Level_3();
	add_backButton();
}
void select::add_background()
{
	auto background = Sprite::create("pictures/icon/select.jpg");
	background->setScale(1.2);
	background->setPosition(Vec2(450, 300));
	this->addChild(background, 0);
}
void select::add_music()
{
	/*设置背景音乐*/
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/select.mp3", true);  /*设置为true，重复播放*/
}
void select::add_Level_1()
{
	Level_1 = Sprite::create("pictures/icon/Level_1.png");
	Level_1->setPosition(Vec2(120,500));
	this->addChild(Level_1, 2);
	init_Level_1_event();
}
void select::init_Level_1_event()
{
	auto Level_1Listener = EventListenerTouchOneByOne::create();
	Level_1Listener->onTouchBegan = CC_CALLBACK_2(select::touch_Level_1_began, this);
	Level_1Listener->onTouchEnded = CC_CALLBACK_2(select::touch_Level_1_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Level_1Listener, Level_1);
}
bool select::touch_Level_1_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		return true;
	}
	return false;
}
bool select::touch_Level_1_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		stop_music();
		auto scene = Level_1::createScene();     /*创建第一关场景*/
		this->removeAllChildren();
		Director::getInstance()->replaceScene(scene);
		return true;
	}
	return false;
}

void select::add_Level_2()
{
	Level_2 = Sprite::create("pictures/icon/Level_2.png");
	Level_2->setPosition(Vec2(250,500));
	this->addChild(Level_2, 2);
	init_Level_2_event();
}
void select::init_Level_2_event()
{
	auto Level_2Listener = EventListenerTouchOneByOne::create();
	Level_2Listener->onTouchBegan = CC_CALLBACK_2(select::touch_Level_2_began, this);
	Level_2Listener->onTouchEnded = CC_CALLBACK_2(select::touch_Level_2_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Level_2Listener, Level_2);
}
bool select::touch_Level_2_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		return true;
	}
	return false;
}
bool select::touch_Level_2_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		if (level_1_ready)
		{
			stop_music();
			auto scene = Level_2::createScene();     /*创建第二关场景*/
			Director::getInstance()->replaceScene(scene);
			this->removeAllChildren();
			return true;
		}
	}
	return false;
}

void select::add_Level_3()
{
	Level_3 = Sprite::create("pictures/icon/Level_3.png");
	Level_3->setPosition(Vec2(400,500));
	this->addChild(Level_3, 2);
	init_Level_3_event();
}
void select::init_Level_3_event()
{
	auto Level_3Listener = EventListenerTouchOneByOne::create();
	Level_3Listener->onTouchBegan = CC_CALLBACK_2(select::touch_Level_3_began, this);
	Level_3Listener->onTouchEnded = CC_CALLBACK_2(select::touch_Level_3_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Level_3Listener, Level_3);
}
bool select::touch_Level_3_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		return true;
	}
	return false;
}
bool select::touch_Level_3_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		if (level_2_ready)  /*第二关通关了*/
		{
			stop_music();
			auto scene = Level::createScene();     /*创建第三关场景*/
			Director::getInstance()->replaceScene(scene);
			this->removeAllChildren();
			return true;
		}
	}
	return false;
}
void select::add_backButton()
{
	backButton = Sprite::create("pictures/icon/exit.png");
	backButton->setPosition(Vec2(80,30));
	this->addChild(backButton, 2);
	init_backButton_event();
}
void select::init_backButton_event()
{
	auto backListener = EventListenerTouchOneByOne::create();
	backListener->onTouchBegan = CC_CALLBACK_2(select::touch_backButton_began, this);
	backListener->onTouchEnded = CC_CALLBACK_2(select::touch_backButton_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, backButton);
}
bool select::touch_backButton_began(Touch* t, Event* e)
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
bool select::touch_backButton_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
		stop_music();
		this->removeAllChildren();
		back_start();
		return true;
	}
	sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
	return false;
}
void select::back_start()
{
	auto scene = PVZ::createScene();
	Director::getInstance()->replaceScene(scene);
}
void select::stop_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopAllEffects();
}