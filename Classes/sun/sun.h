#pragma once
USING_NS_CC;
class sun:public Sprite
{
    bool is_move = 0;
    bool busy = 0;
public:
    Sprite* sprite;
    sun(Sprite*outside_sprite);
    ~sun();
    virtual void update(float dt);
    bool getState() { return busy; };
    void setBusy() { busy = true; };
    void sun_init();
    void create();
    void init_listener();
    void move();
    void fall();
    void play_music();
};