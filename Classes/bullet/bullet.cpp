#include "PVZ.h"
USING_NS_CC;
Bullet::Bullet(cocos2d::Node*parent)
{
	Sprite::onEnter();
	sprite = Sprite::create("pictures/bullet/pea.png");
	parent->addChild(sprite, 3);
}
Bullet::~Bullet()
{
	Sprite::onExit();
}
void Bullet::get_line()
{
	int i = static_cast<int>((570 - position.y + 13) / 100);
	/*加13是因为子弹的位置会比初始位置高13，这样才能和豌豆射手的嘴水平*/
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