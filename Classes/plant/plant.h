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
    int line;            /*��Ӧ����*/
    int row;             /*��Ӧ����*/
    Vec2 position;
    Sprite* sprite;     /*��Ӧ����*/
    double blood = 500;   /*��ǰѪ��*/
    Plant(Sprite* outside_sprite);
    ~Plant();
    virtual void plant_init();
    void die();
    void setBasic(std::string FrameDir,int wait_num);
    virtual void wait();
    virtual void loadResource();
    virtual void init_wait_animate();
};
/*����Ϊֲ��������*/

class BulletShooter :public Plant
{
    double attack = 100;     /*���ι������˺�ֵ*/
    int size = 0;            /*���ڼ�¼��ǰ���ϵĽ�ʬ���������Ϊ0�򲻷����ӵ�*/
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
