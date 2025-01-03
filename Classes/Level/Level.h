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

    int per = 60;     /*单次出怪概率*/
    int level = 1;    /*当前关卡标记*/
    int sun_interval = 5 * 60;    /*太阳生成的时间间隔*/
    int ready_interval = 6 * 60;      /*僵尸开始生成前的准备时间*/
    int zombie_interval = 15 * 60;      /*第一次生成僵尸的间隔点，总得久一点不然不用玩了*/
    //int time=4*60*60;                      /*单位为 分*秒*帧数,总时间*/
    int zombie_total = 50;
    int flush_time = 2000;       /*一大波僵尸释放总时间*/
    int win_time = 280;          /*胜利动画所用时间*/
    int num_1 = 0;
    int num_2 = 0;
    int num_3 = 0;
    int num_4 = 0;
    int num_5 = 0;
    /*以上用于纪录当前生成的僵尸在行上的分布，总不能运气太差全生成在一行了，强行调整一下*/
    int Buckethead_num = 6;        /*铁通僵尸总数*/
    bool is_play = 0;        /*用于标识是否播放了一大波僵尸的动画*/
    bool is_win_play = 0;           /*标识胜利动画是否播放*/
    bool is_flush = 0;        /*用于判断当前波次是否释放完全*/
    LevelState* current_state = new ReadyState();


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
    void init_exitButton_event();
    bool touch_exitButton_began(Touch* t, Event* e);
    bool touch_exitButton_end(Touch* t, Event* e);
    /*退出选项相关函数如上*/

    /*菜单选项相关函数如上*/
    virtual void flush();        /*一大波僵尸来时进行的操作*/

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
    void flush();
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Level_1);
};
class Level_2 :public Level
{
    void set_level_ready();
    void addcard();
    void flush();
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(Level_2);
};
/*关卡类*/


