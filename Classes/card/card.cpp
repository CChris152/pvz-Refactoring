#include "PVZ.h"
USING_NS_CC;
void Card::card_init(cocos2d::Node*parent,Behavior *behavior)
{
	sprite = Sprite::create();
	parent->addChild(sprite, 2);
	this->behavior = behavior;
	this->behavior->load(sprite);
	init_listener();
}
void Card::init_listener()
{
	_eventDispatcher->removeEventListenersForTarget(sprite);  /*因为要反复调用，因此先将其他在sprite上的监听器移除*/
	/*启动非点击状态时的监听器*/
	auto cardListener = EventListenerTouchOneByOne::create();
	cardListener->onTouchBegan = CC_CALLBACK_2(Card::touch_began, this);
	cardListener->onTouchEnded = CC_CALLBACK_2(Card::touch_end, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, sprite);
}
bool Card::touch_began(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	auto now = static_cast<Sprite*>(e->getCurrentTarget());       /*取得当前坐标的对象*/
	if (now->getBoundingBox().containsPoint(pt))
	{
		is_select = 1;     /*标记为点击状态，执行另一个鼠标监视器函数*/
		return true;
	}
	return false;
}
bool Card::touch_end(Touch* t, Event* e)
{
	Vec2 pt = t->getLocation();
	auto now = static_cast<Sprite*>(e->getCurrentTarget());
	if (now->getBoundingBox().containsPoint(pt))
	{
		if (total >= behavior->getCost())
		{
			behavior->setTextureSelect(sprite);
			init_listener_select();
			return true;
		}
	}
	return false;
}
void Card::init_listener_select()
{
	_eventDispatcher->removeEventListenersForTarget(sprite);  /*因为要反复调用，因此先将其他在sprite上的监听器移除*/
	/*启动点击状态时的监听器*/
	_eventDispatcher->removeEventListenersForTarget(sprite);
	auto cardListener = EventListenerTouchOneByOne::create();
	cardListener->onTouchBegan = CC_CALLBACK_2(Card::touch_began_select, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cardListener, sprite);
}
bool Card::touch_began_select(Touch*t,Event*e)
{
	Vec2 pt = t->getLocation();      /*得到当前坐标*/
	behavior->checkPlant(pt,sprite);
	is_select = 0;     /*标记为非点击状态，执行另一个鼠标监视器函数*/
	is_used = 1;
	behavior->setTextureOrigin(sprite);
	init_listener();               /*切换为另一个监听器*/
	return false;
}



void Behavior::load(Sprite*sprite)
{
	sprite->setTexture(OriginTexture);
	sprite->setPosition(position);
}
void Behavior::plant_music()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Music/plant.mp3", false, 1.0f, 1.0f, 1.0f);
}
void Behavior::setTextureOrigin(Sprite* sprite)
{
	sprite->setTexture(OriginTexture);
}
void Behavior::setTextureSelect(Sprite* sprite)
{
	sprite->setTexture(SelectTexture);
}
bool Behavior::is_empty(Vec2 pt)
{
	int row, line;
	/*因为没有四舍五入，所以先加上50在进行计算*/
	row = static_cast<int>((fabs(pt.x - 125 + 50)) / 85);
	line = static_cast<int>((fabs(470 + 50 - pt.y)) / 100);
	if (row >= 0 && row < 9)
		if (line >= 0 && line < 5)
			if (board[line][row] == NULL)
				return true;
	return false;
}
bool Behavior::is_in_board(Vec2 pt)
{
	const float blocks[] = { BLOCK_1, BLOCK_2, BLOCK_3, BLOCK_4, BLOCK_5, BLOCK_6, BLOCK_7, BLOCK_8, BLOCK_9 };
	const float lines[] = { LINE_1, LINE_2, LINE_3, LINE_4, LINE_5 };

	for (float block : blocks) {
		if (fabs(pt.x - block) < 20.0f) {
			for (float line : lines) {
				if (fabs(pt.y - line) < 20.0f) {
					return true; // 如果在某个块的范围内，返回 true
				}
			}
		}
	}
	return false; // 如果没有找到匹配的块和行，返回 false
}
void Behavior::checkPlant(Vec2 pt,Sprite*sprite)
{
	if (total >= cost)
	{
		if (is_in_board(pt))
		{
			if (is_empty(pt))  /*进行放置植物操作*/
			{
				total -= cost;
				add_plant(pt,sprite->getParent());
				plant_music();
			}
		}
	}
}

void BulletShooterCardBehavior::add_plant(Vec2 pt, cocos2d::Node* parent)
{
	int row = static_cast<int>((pt.x - 75) / 85);
	int line = static_cast<int>((520 - pt.y) / 100);
	PlantFactory::add_bulletShooter(row, line, parent);
}
void SunflowerCardBehavior::add_plant(Vec2 pt, cocos2d::Node* parent)
{
	int row = static_cast<int>((pt.x - 75) / 85);
	int line = static_cast<int>((520 - pt.y) / 100);
	PlantFactory::add_sunflower(row, line, parent);
}
void NutCardBehavior::add_plant(Vec2 pt, cocos2d::Node* parent)
{
	int row = static_cast<int>((pt.x - 75) / 85);
	int line = static_cast<int>((520 - pt.y) / 100);
	PlantFactory::add_nut(row, line, parent);
}
void PotatoMineCardBehavior::add_plant(Vec2 pt, cocos2d::Node* parent)
{
	int row = static_cast<int>((pt.x - 75) / 85);
	int line = static_cast<int>((520 - pt.y) / 100);
	PlantFactory::add_potatoMine(row, line, parent);
}