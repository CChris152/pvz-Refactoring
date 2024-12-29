#pragma once
class card :public Sprite
{
protected:
    bool is_select = 0;  /*用于记录是否被点击过*/
    bool is_used = 0;    /*用于记录是否成功放置过植物*/
    int cost;
public:
    Sprite* sprite;
    Sprite* tmp;
    ~card();
    void update(float dt);
    virtual void card_init();
    void plant_music();
    void init_listener();
    void set_picture();
    bool touch_began(Touch* t, Event* e);
    bool move(Touch* t, Event* e);
    bool is_empty(Vec2 pt);                  /*判断是否点击处有植物*/
    bool is_in_board(Vec2 pt);               /*判断是否点击在格子当中*/

    /*部分监听器涉及到对卡片图案的改变，要进行重写*/
    virtual bool touch_end(Touch* t, Event* e);
    void init_listener_select();
    bool touch_began_select(Touch* t, Event* e);
    virtual void add_plant(double row,double line);
};
/*卡片基类，以豌豆射手为原型*/
class sunflower_card :public card
{
    void init_listener();
    void init_listener_select();
    bool touch_end(Touch* t, Event* e);
    bool touch_began_select(Touch* t, Event* e);
    void add_plant(double row, double line);
public:
    void card_init();
};
class nut_card :public card
{
    void init_listener();
    void init_listener_select();
    bool touch_end(Touch* t, Event* e);
    bool touch_began_select(Touch* t, Event* e);
    void add_plant(double row, double line);
public:
    void card_init();
};
class potato_mine_card :public card
{
    void init_listener();
    void init_listener_select();
    bool touch_end(Touch* t, Event* e);
    bool touch_began_select(Touch* t, Event* e);
    void add_plant(double roe, double line);
public:
    void card_init();
};