#pragma once
#include"cocos2d.h"
USING_NS_CC;
class plant :public Sprite
{
    double attack = 100;     /*单次攻击的伤害值*/
    int interval =4   *60;    /*使用帧定时器，因此60为单位秒*/
    int size;            /*用于纪录当前行上的僵尸数量，如果为0则不发射子弹*/
    bool is_attack;
    bool is_wait;
    bool is_die;
    Vector<SpriteFrame*> waitFrames;
    std::vector<SpriteFrame*>asd;
public:
    int line;            /*对应行数*/
    int row;             /*对应列数*/
    Vec2 position;
    Sprite* sprite;     /*对应精灵*/
    double blood = 500;   /*当前血量*/
    plant(Sprite* outside_sprite);
    ~plant();
    virtual void update(float dt);
    virtual void plant_init();
    void shoot();
    void die();
    virtual void wait();
    virtual void loadResource();
    virtual void init_animate();
    virtual void init_wait_animate();
    virtual void init_sound();
};
/*以上为植物抽象基类*/



class sunflower :public plant
{
    int create_interval = 15 * 60;   /*创建阳光的时间间隔*/
    void create_sun();
    void plant_init();
    Vector<SpriteFrame*> waitFrames;
public:
    sunflower(Sprite* outside_sprite);
    void wait();
    void loadResource();
    void init_animate();
    void update(float dt);
};


/*以上为向日葵类，继承植物基类来减少代码量*/
class nut :public plant
{
    void plant_init();
    Vector<SpriteFrame*> waitFrames;
public:
    nut(Sprite* outside_sprite);
    void wait();
    void loadResource();
    void init_animate();
    void update(float dt);
};


/*以上为坚果墙类，继承植物基类来减少代码量*/
class potato_mine :public plant
{
    bool is_ready = 0;
    int start_interval = 5 * 60;
    void plant_init();
    void play_music();     /*播放爆炸音乐*/
    Vector<SpriteFrame*> waitFrames;
    Vector<SpriteFrame*> readyFrames;
public:
    potato_mine(Sprite* outside_sprite);
    void ready();
    void wait();
    void loadResource();
    void init_animate();
    void update(float dt);
};

/*以上为土地雷类*/