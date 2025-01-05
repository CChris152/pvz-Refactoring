

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include<vector>
#include<sun/sun.h>
#include<bullet/bullet.h>
#include<card/card.h>
#include<level/level.h>
#include<plant/plant.h>
#include<factory/factory.h>
#include<car/car.h>
#include<zombie/zombie.h>
#include<select/select.h>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include<LevelState/LevelState.h>
#include<SpriteClick/SpriteClick.h>
using namespace CocosDenshion;
USING_NS_CC;
#define LINE_1 470.0
#define LINE_2 370.0
#define LINE_3 270.0
#define LINE_4 170.0
#define LINE_5 70.0
/*以上为行数对应的高度(从上到下）*/
#define END_POSITION 0.0
#define CAR_POSITION 50.0
#define BLOCK_1 125.0
#define BLOCK_2 210.0
#define BLOCK_3 295.0
#define BLOCK_4 380.0
#define BLOCK_5 465.0
#define BLOCK_6 550.0
#define BLOCK_7 635.0
#define BLOCK_8 720.0
#define BLOCK_9 805.0
#define START_POSITION 980.0
/*以上为从左到右格子数对应的位置*/


#define SUN_START 700.0  /*太阳掉落时的初始位置*/
#define BULLET_SHOOT 4*60
#define SUNFLOWER_CREATE 20*60
#define SUN_CREATE 12*60
#define ZOMBIE_CREATE 20*60


#define SUN_DURATION  5*60
#define READY_DURATION 6*60
#define FLUSH_DURATION 2*60*60 + READY_DURATION
/*以上为相应动作时间间隔*/
class PVZ : public cocos2d::Scene
{
    Size visibleSize;
    void addBackground();
    void addmusic();
    void get_progress();    /*读取当前关卡进展*/
    void loadResource();
    void stopmusic();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(PVZ);
};
/*初始页面类*/


template<typename Action = std::function<void()>>
class ButtonTemplate {
public:
	ButtonTemplate(Scene* scene,
		const std::string& spritePath,
		const Vec2& position,
		Action&& action,
		bool* unlockFlag = nullptr)
		: scene_(scene)
		, spritePath_(spritePath)
		, position_(position)
		, action_(std::forward<Action>(action))
		, unlockFlag_(unlockFlag)
	{
		initButton();
	}

	void initButton() {
		sprite_ = Sprite::create(spritePath_);
		sprite_->setPosition(position_);
		scene_->addChild(sprite_, 2);
		initEvent();
	}

	void initEvent() {
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(ButtonTemplate::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(ButtonTemplate::onTouchEnded, this);
		// 使用 Director 来获取 EventDispatcher
		Director::getInstance()->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(listener, sprite_);
	}

	bool onTouchBegan(Touch* t, Event* e) {
		Vec2 pt = t->getLocation();
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		return sprite->getBoundingBox().containsPoint(pt);
	}

	bool onTouchEnded(Touch* t, Event* e) {
		Vec2 pt = t->getLocation();
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		if (sprite->getBoundingBox().containsPoint(pt)) {
			if (!unlockFlag_ || *unlockFlag_) {
				if (auto selectScene = dynamic_cast<Scene*>(scene_)) {
					select::stop_music();
				}
				action_();
				return true;
			}
		}
		return false;
	}

private:
	Scene* scene_;
	Sprite* sprite_;
	std::string spritePath_;
	Vec2 position_;
	Action action_;
	bool* unlockFlag_;
};


extern Plant* board[5][9];
extern std::vector<Zombie*>line_1;
extern std::vector<Zombie*>line_2;
extern std::vector<Zombie*>line_3;
extern std::vector<Zombie*>line_4;
extern std::vector<Zombie*>line_5;
extern std::vector<sun*>sunPool;
extern std::vector<Bullet*>all_bullet;
extern car* all_car[5];
extern int total;
extern bool level_1_ready;
extern bool level_2_ready;
/*data cpp里存储的数据*/
#endif 
