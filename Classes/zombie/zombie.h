#pragma once
#include"cocos2d.h"
USING_NS_CC;
#define NORMAL 0
#define FLAG   1
#define BUCKETHEAD 2
class zombie :public Sprite
{
protected:
    double attack = 300;
    double speed = 60;          /*到达终点所用时间，单位为秒*/
    unsigned int eat_music;         /*纪录吃植物音效的id*/
    Vector<SpriteFrame*> eatFrames;
    Vector<SpriteFrame*> waitFrames;
    Vector<SpriteFrame*> moveFrames;
    Vector<SpriteFrame*> dieFrames;
public:
    int type;
    double blood = 1200;
    Sprite* sprite;
    Vec2 position;
    int die_time = 1*60;       /*死亡动画播放时间*/
    int line;             /*纪录生成的行数*/
    int row;
    int interval = 120;
    bool is_move=0;
    bool is_eat=0;
    bool is_die=0;
    bool is_wait=0;
    zombie(Sprite* outside_sprite, double line);
    ~zombie();
    void die();
    bool judge_eat();
    virtual void update(float dt);
    virtual void loadResource();
    void eatmusic();
    void stopmusic();
    void init_animate();
    /*以下为对应动画创建*/
    void eat();
    void wait();
    virtual void move();
    virtual void init_move_animate();
    virtual void init_eat_animate();
    virtual void init_wait_animate();
    virtual void init_die_animate();
};
/*僵尸类*/
class flag_zombie :public zombie
{
    void init_eat_animate();
    void init_move_animate();
public:
    flag_zombie(Sprite* outside_sprite, double outside_line);
};
class Buckethead_zombie :public zombie
{
    void init_eat_animate();
    void init_move_animate();
public:
    Buckethead_zombie(Sprite* outside_sprite, double outside_line);
};