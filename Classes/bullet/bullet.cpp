#include "PVZ.h"
USING_NS_CC;
Sprite* Bullet::sharedSprite = nullptr;
Bullet::Bullet(cocos2d::Node* parent)
{
	Sprite::onEnter();
	if (!sharedSprite) {
		sharedSprite = Sprite::create("pictures/bullet/pea.png"); // 只创建一次
		if (!sharedSprite) {
			CCLOG("Failed to create sharedSprite");
		}
		else {
			sharedSprite->retain(); // 保持对纹理的引用
		}
	}
	sprite = Sprite::createWithTexture(sharedSprite->getTexture()); // 创建新的Sprite实例
	parent->addChild(sprite, 3);
}
Bullet::~Bullet()
{
	if (sharedSprite) {
		sharedSprite->release(); // 释放纹理引用
		sharedSprite = nullptr; // 避免悬空指针
	}
	this->unscheduleUpdate();
	Sprite::onExit();
}
void Bullet::get_line()
{
	int i = static_cast<int>((570 - position.y + 13) / 100);
	line = i;

	switch (line)
	{
	case 0: current_line = &line_1; break;
	case 1: current_line = &line_2; break;
	case 2: current_line = &line_3; break;
	case 3: current_line = &line_4; break;
	case 4: current_line = &line_5; break;
	}
}
void Bullet::move()
{
	auto moveby = MoveBy::create(4, Vec2(START_POSITION, 0));
	sprite->runAction(moveby);
}
void Bullet::update(float dt)
{
	position = sprite->getPosition();
	is_zombie();
}
void Bullet::load(Vec2 position)
{
	sprite->setPosition(Vec2(position.x + 20, position.y + 13));
	this->position = sprite->getPosition();
	get_line();
	Bullet::move();
	scheduleUpdate();
}
void Bullet::is_zombie()
{
	if (current_line)
	{
		for (auto it = current_line->begin(); it < current_line->end(); it++)
		{
			if (position.x - (*it)->position.x < 20 && position.x - (*it)->position.x > 0)
			{
				playHitSound((*it)->type);
				(*it)->blood -= attack;
				(sprite->getParent())->removeChild(sprite);
				unscheduleUpdate();
				break;
			}
		}
	}
}
void Bullet::playHitSound(int type)
{
	auto audio = SimpleAudioEngine::getInstance();
	if (type == 2) {
		audio->playEffect("Music/shieldhit.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	else {
		audio->playEffect("Music/bullet_hit.mp3", false, 1.0f, 1.0f, 1.0f);
	}
}