

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include<vector>
#include<sun/sun.h>
#include<bullet/bullet.h>
#include<card/card.h>
#include<level/level.h>
#include<plant/plant.h>

#include<car/car.h>
#include<zombie/zombie.h>
#include<select/select.h>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
#define LINE_1 470.0
#define LINE_2 370.0
#define LINE_3 270.0
#define LINE_4 170.0
#define LINE_5 70.0
/*以上为行数对应的高度(从上到下）*/
#define END_POSITION 0.0
#define CAR_POSITION 50.0
#define BLOCK_1 125.0
#define BLOCK_2 210.0
#define BLOCK_3 295.0
#define BLOCK_4 380.0
#define BLOCK_5 465.0
#define BLOCK_6 550.0
#define BLOCK_7 635.0
#define BLOCK_8 720.0
#define BLOCK_9 805.0
#define START_POSITION 980.0
/*以上为从左到右格子数对应的位置*/


#define SUN_START 700.0  /*太阳掉落时的初始位置*/
#define BULLET_SHOOT 4*60
#define SUNFLOWER_CREATE 20*60
#define SUN_CREAT 12*60
#define ZOMBIE_CREATE 20*60
/*以上为相应动作时间间隔*/
class PVZ : public cocos2d::Scene
{
    Size visibleSize;
    Sprite* startButton;
    Sprite* exitButton;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void addBackground();
    void addmusic();
    void addstartButton();
    void init_startButton_event();
    bool touch_startButton_began(Touch* t, Event* e);
    bool touch_startButton_end(Touch* t, Event* e);

    void addexitButton();
    void init_exitButton_event();
    bool touch_exitButton_began(Touch* t, Event* e);
    bool touch_exitButton_end(Touch* t, Event* e);

    void get_progress();    /*读取当前关卡进展*/
    void loadResource();
    void stopmusic();
    void end();       /*结束游戏*/
    CREATE_FUNC(PVZ);
};
/*初始页面类*/
extern plant* board[5][9];
extern std::vector<zombie*>line_1;
extern std::vector<zombie*>line_2;
extern std::vector<zombie*>line_3;
extern std::vector<zombie*>line_4;
extern std::vector<zombie*>line_5;
extern std::vector<bullet*>all_bullet;
extern std::vector<sun*>all_sun;
extern car* all_car[5];
extern int total;
extern bool level_1_ready;
extern bool level_2_ready;
/*data cpp里存储的数据*/
#endif 
