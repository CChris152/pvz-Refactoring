#include "PVZ.h"
USING_NS_CC;
sun::sun(Sprite*outside_sprite)
{
	Sprite::onEnter();
	sprite=outside_sprite;
	sun_init();
}
sun::~sun()
{
	sprite->getParent()->removeChild(sprite);
	Sprite::onExit();
}
void sun::sun_init()
{
	busy = true;
	init_listener();
	this->scheduleUpdate();
}
void sun::update(float dt)
{
	Vec2 pt=sprite->getPosition();
	if (fabs(pt.x-105)+fabs(pt.y-545)<5&&is_move==1)    
		/*Ϊ�˷�ֹ˵��Ȼ����ʱ����(105,545)λ�þͱ������ʹ��is_move���ж��Ƿ񱻵��*/
	{
		sprite->setOpacity(0);
		sprite->getEventDispatcher()->removeEventListenersForTarget(sprite);
		busy = false;
		is_move = false;
		total += 50;
		this->unscheduleUpdate();
	}
}
void sun::init_listener()
{
	auto sunListener = EventListenerTouchOneByOne::create();

	// ʹ��Lambda���ʽ�򻯴�������
	sunListener->onTouchBegan = [](Touch* t, Event* e) {
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		return sprite->getBoundingBox().containsPoint(t->getLocation());
		};

	sunListener->onTouchEnded = [this](Touch* t, Event* e) {
		auto sprite = static_cast<Sprite*>(e->getCurrentTarget());
		if (sprite->getBoundingBox().containsPoint(t->getLocation())) {
			play_music();
			move();
			return true;
		}
		return false;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(sunListener, sprite);
}
void sun::play_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/sun.mp3", false);
	CCLOG("STATE:%d,MOVE:%d", this->busy,this->is_move);
}
void sun::move()
{
	auto moveto = MoveTo::create(0.5,Vec2(105,545));
	sprite->stopAllActions();
	sprite->runAction(moveto);
	is_move = 1;
}
void sun::create()
{
	/*ִ�����ⱻ����ʱ����������*/
	auto up = MoveBy::create(1, Vec2(5, 50));
	auto down = MoveBy::create(1, Vec2(5, -75));
	auto seq = Sequence::create(up,down, nullptr);
	sprite->runAction(seq);
}
void sun::fall()
{
	int distance = 200 + rand() % 400;    /*��������λ����[200,600)*/
	auto moveto = MoveTo::create(30, Vec2(sprite->getPosition().x, -distance));
	sprite->runAction(moveto);
}