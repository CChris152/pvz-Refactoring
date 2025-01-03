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

	// 定义按钮信息结构
	struct ButtonInfo {
		std::string normalImage;
		std::string selectedImage;
		Vec2 position;
		std::function<void()> callback;
	};

	// 定义所有按钮的信息
	std::vector<ButtonInfo> buttons = {
		{
			"pictures/icon/begin.png",
			"pictures/icon/begin_select.png",
			Vec2(600, 450),
			[this]() {
				stopmusic();
				auto scene = select::createScene();
				Director::getInstance()->replaceScene(scene);
			}
		},
		{
			"pictures/icon/exit.png",
			"pictures/icon/exit_select.png",
			Vec2(850, 570),
			[this]() {
				Director::getInstance()->end();
			}
		}
	};

	// 添加所有按钮
	for (const auto& button : buttons) {
		auto sprite = Sprite::create(button.normalImage);
		sprite->setPosition(button.position);
		this->addChild(sprite, 1);

		auto listener = EventListenerTouchOneByOne::create();

		// 触摸开始
		listener->onTouchBegan = [button](Touch* t, Event* e) {
			Vec2 pt = t->getLocation();
			auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
			if (sprite->getBoundingBox().containsPoint(pt)) {
				sprite->setTexture(button.selectedImage);
				return true;
			}
			return false;
			};

		// 触摸结束
		listener->onTouchEnded = [this, button](Touch* t, Event* e) {
			Vec2 pt = t->getLocation();
			auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
			sprite->setTexture(button.normalImage);
			if (sprite->getBoundingBox().containsPoint(pt)) {
				button.callback();
				return true;
			}
			return false;
			};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, sprite);
	}
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
