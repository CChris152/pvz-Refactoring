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

	// 添加关卡按钮
	struct LevelInfo {
		std::string image;
		Vec2 position;
		std::function<void()> callback;
		bool condition;
	};

	std::vector<LevelInfo> levels = {
		{
			"pictures/icon/Level_1.png",
			Vec2(120, 500),
			[this]() {
				stop_music();
				auto scene = Level_1::createScene();
				Director::getInstance()->replaceScene(scene);
			},
			true  // 第一关总是可用
		},
		{
			"pictures/icon/Level_2.png",
			Vec2(250, 500),
			[this]() {
				stop_music();
				auto scene = Level_2::createScene();
				Director::getInstance()->replaceScene(scene);
			},
			level_1_ready  // 需要通过第一关
		},
		{
			"pictures/icon/Level_3.png",
			Vec2(400, 500),
			[this]() {
				stop_music();
				auto scene = Level::createScene();
				Director::getInstance()->replaceScene(scene);
			},
			level_2_ready  // 需要通过第二关
		}
	};

	// 添加所有关卡按钮
	for (const auto& level : levels) {
		auto levelSprite = Sprite::create(level.image);
		levelSprite->setPosition(level.position);
		this->addChild(levelSprite, 2);

		auto listener = EventListenerTouchOneByOne::create();

		// 触摸开始
		listener->onTouchBegan = [](Touch* t, Event* e) {
			Vec2 pt = t->getLocation();
			auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
			return sprite->getBoundingBox().containsPoint(pt);
			};

		// 触摸结束
		listener->onTouchEnded = [this, level](Touch* t, Event* e) {
			Vec2 pt = t->getLocation();
			auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
			if (sprite->getBoundingBox().containsPoint(pt) && level.condition) {
				level.callback();
				this->removeAllChildren();
			}
			return false;
			};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, levelSprite);
	}

	// 添加返回按钮
	auto backButton = Sprite::create("pictures/icon/exit.png");
	backButton->setPosition(Vec2(80, 30));
	this->addChild(backButton, 2);

	auto backListener = EventListenerTouchOneByOne::create();

	backListener->onTouchBegan = [](Touch* t, Event* e) {
		Vec2 pt = t->getLocation();
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		if (sprite->getBoundingBox().containsPoint(pt)) {
			sprite->setTexture("pictures/icon/exit_select.png");
			return true;
		}
		return false;
		};

	backListener->onTouchEnded = [this](Touch* t, Event* e) {
		Vec2 pt = t->getLocation();
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		if (sprite->getBoundingBox().containsPoint(pt)) {
			sprite->setTexture("pictures/icon/exit.png");
			stop_music();
			this->removeAllChildren();
			back_start();
			return true;
		}
		sprite->setTexture("pictures/icon/exit.png");
		return false;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, backButton);
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