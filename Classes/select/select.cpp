#include "PVZ.h"
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
	// 关卡按钮
	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/Level_1.png",
		Vec2(120, 500),
		[this]() {
			auto scene = Level_1::createScene();
			this->removeAllChildren();
			Director::getInstance()->replaceScene(scene);
		});

	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/Level_2.png",
		Vec2(250, 500),
		[this]() {
			auto scene = Level_2::createScene();
			this->removeAllChildren();
			Director::getInstance()->replaceScene(scene);
		},
		&level_1_ready);

	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/Level_3.png",
		Vec2(400, 500),
		[this]() {
			auto scene = Level::createScene();
			this->removeAllChildren();
			Director::getInstance()->replaceScene(scene);
		},
		&level_2_ready);

	// 返回按钮
	new ButtonTemplate<std::function<void()>>(this,
		"pictures/icon/exit.png",
		Vec2(80, 30),
		[this]() {
			this->removeAllChildren();
			this->back_start();
		});

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