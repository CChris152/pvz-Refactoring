#pragma once
USING_NS_CC;
class sun:public Sprite
{
    bool is_move = 0;
public:
    Sprite* sprite;
    sun(Sprite*outside_sprite);
    ~sun();
    virtual void update(float dt);
    void sun_init();
    void create();
    void init_listener();
    bool touch_began(Touch* t, Event* e);
    void move();
    void fall();
    void play_music();
    bool touch_end(Touch* t, Event* e);
};