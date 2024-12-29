/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* PVZ::createScene()
{
	return PVZ::create();
}
// on "init" you need to initialize your instance
bool PVZ::init()
{
	if (!Scene::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize(); /*获取窗口大小*/
	loadResource();             /*加载所有成员*/
	get_progress();
	return true;
}
void PVZ::get_progress()
{
	level_1_ready = UserDefault::getInstance()->getBoolForKey("level_1_ready", 0);
	level_2_ready = UserDefault::getInstance()->getBoolForKey("level_2_ready", 0);
}
void PVZ::loadResource()
{
	addBackground();
	addstartButton();
	addexitButton();
	addmusic();
}
void PVZ::addBackground()
{
	auto Surface = Sprite::create("pictures/icon/Surface.png");          /*背景图片设置*/
	Surface->setPosition(Vec2(450, 300));
	addChild(Surface, 0);      /*放在最下层*/
}
void PVZ::addmusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Music/start.ogg", true);
}

/*开始按钮相关函数*/
void PVZ::addstartButton()     /*添加开始按钮*/
{
	startButton = Sprite::create("pictures/icon/begin.png");
	startButton->setPosition(Vec2(600, 450));
	addChild(startButton, 1);
	init_startButton_event();
}
void PVZ::init_startButton_event()         /*创建开始按钮监听器*/
{
	auto startListener = EventListenerTouchOneByOne::create();
	startListener->onTouchBegan = CC_CALLBACK_2(PVZ::touch_startButton_began, this);
	startListener->onTouchEnded = CC_CALLBACK_2(PVZ::touch_startButton_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(startListener, startButton);
}
bool PVZ::touch_startButton_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		log("began");
		sprite->setTexture("pictures/icon/begin_select.png"); /*将图片变为选择状态*/
		return true;
	}
	return false;
}
bool PVZ::touch_startButton_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		stopmusic();
		auto scene = select::createScene();     /*创建第一关场景*/
		Director::getInstance()->replaceScene(scene);
		return true;
	}
	sprite->setTexture("pictures/icon/begin.png"); /*将图片变为未选择状态*/
	return false;
}


/*退出按钮相关函数*/
void PVZ::addexitButton()      /*添加退出按钮*/
{
	exitButton = Sprite::create("pictures/icon/exit.png");
	exitButton->setPosition(Vec2(850, 570));
	addChild(exitButton, 1);
	init_exitButton_event();
}
void PVZ::init_exitButton_event()      /*创建退出监听器*/
{
	auto exitListener = EventListenerTouchOneByOne::create();
	exitListener->onTouchBegan = CC_CALLBACK_2(PVZ::touch_exitButton_began, this);
	exitListener->onTouchEnded = CC_CALLBACK_2(PVZ::touch_exitButton_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(exitListener, exitButton);
}
bool PVZ::touch_exitButton_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		log("exit-began-true");
		sprite->setTexture("pictures/icon/exit_select.png"); /*将图片变为选择状态*/
		return true;
	}
	log("exit-began-false");
	return false;
}
bool PVZ::touch_exitButton_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
	if (sprite->getBoundingBox().containsPoint(pt))
	{
		sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
		Director::getInstance()->end();      /*退出*/
		return true;
	}
	sprite->setTexture("pictures/icon/exit.png"); /*将图片变为未选择状态*/
	return false;
}
void PVZ::stopmusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}

/*
鼠标点击与精灵绑定参考代码
https://blog.csdn.net/arv002/article/details/132108748?spm=1001.2014.3001.5501
*/