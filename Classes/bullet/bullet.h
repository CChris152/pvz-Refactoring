#pragma once
#include"cocos2d.h"
class Zombie;
USING_NS_CC;
class Bullet :public Sprite
{
private:
    std::vector<Zombie*>* current_line = nullptr;
    static Sprite* sharedSprite; // 静态成员，用于共享纹理
    Sprite* sprite;
    int line;
    Vec2 position;
    double attack = 300;
    void is_zombie();
    void get_line();
    void move();
    void playHitSound(int type);
public:
    Bullet(cocos2d::Node * parent);
    ~Bullet();
    virtual void update(float dt);
    void load(Vec2 position);
};