#pragma once
#include"cocos2d.h"
USING_NS_CC;
class bullet :public Sprite
{
    double attack = 300;
    Vec2 position;
    int line;
public:
    Sprite* sprite;
    bullet(Sprite* outside_sprite);
    ~bullet();
    virtual void update(float dt);
    void move();
    void hit_music();
    void hit_Buckethead_music();
    void get_line();
    void is_zombie();        /*判断周围有没有僵尸*/
};