#pragma once
class Behavior
{
protected:
    Vec2 position;
    int cost;
    std::string OriginTexture;
    std::string SelectTexture;
    void plant_music();
    bool is_empty(Vec2 pt);
    bool is_in_board(Vec2 pt);
public:
    void load(Sprite*sprite);
    void checkPlant(Vec2 pt,Sprite*sprite);
    int getCost() { return cost; };
    void setTextureSelect(Sprite* sprite);
    void setTextureOrigin(Sprite* sprite);
    virtual void add_plant(Vec2 pt,cocos2d::Node*parent)=0;
};
class BulletShooterCardBehavior :public Behavior
{
public:
    BulletShooterCardBehavior()
    {
        position = Vec2(170, 550);
        cost = 100;
        OriginTexture = "pictures/card/bullets_shooter.png";
        SelectTexture = "pictures/card/bullet_shooter_select.png";
    };
    void add_plant(Vec2 pt, cocos2d::Node* parent);
};
class SunflowerCardBehavior :public Behavior
{
public:
    SunflowerCardBehavior()
    {
        position = Vec2(240, 550);
        cost = 50;
        OriginTexture = "pictures/card/sunflower.png";
        SelectTexture = "pictures/card/sunflower_select.png";
    };
    void add_plant(Vec2 pt, cocos2d::Node* parent);
};
class NutCardBehavior :public Behavior
{
public:
    NutCardBehavior()
    {
        position = Vec2(310, 550);
        cost = 50;
        OriginTexture = "pictures/card/nut.png";
        SelectTexture = "pictures/card/nut_select.png";
    };
    void add_plant(Vec2 pt, cocos2d::Node* parent);
};
class PotatoMineCardBehavior :public Behavior
{
public:
    PotatoMineCardBehavior()
    {
        position = Vec2(380, 550);
        cost = 25;
        OriginTexture = "pictures/card/potato_mine.png";
        SelectTexture = "pictures/card/potato_mine_select.png";
    };
    void add_plant(Vec2 pt, cocos2d::Node* parent);
};
class Card :public Sprite
{
protected:
    bool is_select = 0;  /*用于记录是否被点击过*/
    bool is_used = 0;    /*用于记录是否成功放置过植物*/
    Behavior* behavior;
public:
    Sprite* sprite;
    void card_init(cocos2d::Node*parent,Behavior* behavior);
    void init_listener();
    bool touch_began(Touch* t, Event* e);
    /*部分监听器涉及到对卡片图案的改变，要进行重写*/
    virtual bool touch_end(Touch* t, Event* e);
    void init_listener_select();
    bool touch_began_select(Touch* t, Event* e);
};