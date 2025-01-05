#pragma once
#include"cocos2d.h"
#include "ui/CocosGUI.h"
#include"LevelState/LevelState.h"
USING_NS_CC;

class Level :public cocos2d::Scene
{
    Size visibleSize;
    Sprite* exitButton;
    Sprite* loadingBar;
    Sprite* shovel;
protected:
    Card bulletShooterCard;
    Card sunflowerCard;
    Card nutCard;
    Card potatoMineCard;
    Label* sun_total;

    int sun_duration = 0;
    int ready_duration = 0;

    LevelState* current_state;


    void off_car();
    void off_sun();
    void off_zombie_schedule();
    void off_plant_schedule();
    void off_bullet_schedule();
    /*析构相关函数如上*/
    void addbackground();
    void addloadingBar();
    virtual void addcard();      /*不同关卡可用卡片不同，继承类进行重写*/
    void addlabel();
    void addshop();            /*加载商店*/
    void addcar();
    void addmusic();
    void addshovel();
    void init_shovel();
    bool touch_shovel_began(Touch* t, Event* e);
    bool touch_shovel_end(Touch* t, Event* e);
    /*铲子相关函数如上*/
    void addexitButton();
    /*退出选项相关函数如上*/

    /*菜单选项相关函数如上*/

    /*以上为动态添加单位函数*/
    bool is_in_board(Vec2 pt);
    bool is_empty(Vec2 pt);

    void stop_plant();
    void stop_bullet();
    void stop_sun();
    void stop_zombie();
    void stop_music();
private:
    int time = 0;
public:
    ~Level();
    virtual void set_level_ready() {};  /*完成关卡时用于纪录胜利情况*/
    template <typename T>
    void off_schedule(std::vector<T*>& vec);
    void stop();
    void addzombie();    /*这个是周期性添加僵尸的函数，不是单独加僵尸的函数*/
    void back_to_select();
    void setState(LevelState* state);
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void loadResoure();         /*加载所有精灵成员*/
    /*初始化相关函数如上*/
    virtual void update(float dt);
    /*refectoring*/
    int getTime();
    /*游戏进行函数如上*/
    CREATE_FUNC(Level);
};
/*关卡基类，以第三关为最终形态*/
class Level_1 :public Level
{
    void set_level_ready();
    void addcard();
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Level_1);
};
class Level_2 :public Level
{
    void set_level_ready();
    void addcard();
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Level_2);
};
/*关卡类*/


