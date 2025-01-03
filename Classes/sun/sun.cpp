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
		/*为了防止说自然掉落时到达(105,545)位置就被清除，使用is_move来判断是否被点击*/
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
	sunListener->onTouchBegan = CC_CALLBACK_2(sun::touch_began, this);
	sunListener->onTouchEnded = CC_CALLBACK_2(sun::touch_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(sunListener, sprite);
}
bool sun::touch_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto now = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (now->getBoundingBox().containsPoint(pt))
	{
		return true;
	}
	return false;
}
bool sun::touch_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto now = static_cast<Sprite*>(e->getCurrentTarget());
	if (now->getBoundingBox().containsPoint(pt))
	{
		play_music();
		this->move();
		return true;
	}
	return false;
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
	/*执行阳光被创造时的跳动动作*/
	auto up = MoveBy::create(2, Vec2(5, 50));
	auto down = MoveBy::create(2, Vec2(5, -75));
	auto seq = Sequence::create(up,down, nullptr);
	sprite->runAction(seq);
}
void sun::fall()
{
	int distance = 200 + rand() % 400;    /*控制下落位置在[200,600)*/
	auto moveto = MoveTo::create(30, Vec2(sprite->getPosition().x, -distance));
	sprite->runAction(moveto);
}