#pragma once
#include"cocos2d.h"
USING_NS_CC;
class Plant :public Sprite
{
    bool is_attack;
    bool is_wait;
    int wait_num;
protected:
    int interval;

    Vector<SpriteFrame*> waitFrames;
    std::string FrameDir;
public:
    int line;            /*对应行数*/
    int row;             /*对应列数*/
    Vec2 position;
    Sprite* sprite;     /*对应精灵*/
    double blood = 500;   /*当前血量*/
    Plant(Sprite* outside_sprite);
    ~Plant();
    virtual void plant_init();
    void die();
    void setBasic(std::string FrameDir,int wait_num);
    virtual void wait();
    virtual void loadResource();
    virtual void init_wait_animate();
};
/*以上为植物抽象基类*/

class BulletShooter :public Plant
{
    double attack = 100;     /*单次攻击的伤害值*/
    int size = 0;            /*用于纪录当前行上的僵尸数量，如果为0则不发射子弹*/
    void shoot();
public:
    BulletShooter(Sprite * sprite);
    virtual void update(float dt);
};
class Sunflower :public Plant
{
    void create_sun();
public:
    virtual void update(float dt);
    Sunflower(Sprite* sprite);
};
class Nut :public Plant
{
public:
    Nut(Sprite* sprite);
    virtual void update(float dt);
};
class PotatoMine :public Plant
{
    bool is_ready = 0;

    
    void play_music();
    void ready();
    void wait();
public:
    PotatoMine(Sprite* sprite);
    virtual void update(float dt);
};
