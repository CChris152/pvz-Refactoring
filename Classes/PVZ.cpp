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

#include "PVZ.h"
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
	addmusic();
	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/begin.png",
		Vec2(600, 450),
		[this]() {
			stopmusic();
			auto scene = select::createScene();
			Director::getInstance()->replaceScene(scene);
		});
	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/exit.png",
		Vec2(850, 570),
		[this]() {
			Director::getInstance()->end();
		});
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
void PVZ::stopmusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}
