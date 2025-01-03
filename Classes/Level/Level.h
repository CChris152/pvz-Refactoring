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

    int per = 60;     /*���γ��ָ���*/
    int level = 1;    /*��ǰ�ؿ����*/
    int sun_interval = 5 * 60;    /*̫�����ɵ�ʱ����*/
    int ready_interval = 6 * 60;      /*��ʬ��ʼ����ǰ��׼��ʱ��*/
    int zombie_interval = 15 * 60;      /*��һ�����ɽ�ʬ�ļ���㣬�ܵþ�һ�㲻Ȼ��������*/
    //int time=4*60*60;                      /*��λΪ ��*��*֡��,��ʱ��*/
    int zombie_total = 50;
    int flush_time = 2000;       /*һ�󲨽�ʬ�ͷ���ʱ��*/
    int win_time = 280;          /*ʤ����������ʱ��*/
    int num_1 = 0;
    int num_2 = 0;
    int num_3 = 0;
    int num_4 = 0;
    int num_5 = 0;
    /*�������ڼ�¼��ǰ���ɵĽ�ʬ�����ϵķֲ����ܲ�������̫��ȫ������һ���ˣ�ǿ�е���һ��*/
    int Buckethead_num = 6;        /*��ͨ��ʬ����*/
    bool is_play = 0;        /*���ڱ�ʶ�Ƿ񲥷���һ�󲨽�ʬ�Ķ���*/
    bool is_win_play = 0;           /*��ʶʤ�������Ƿ񲥷�*/
    bool is_flush = 0;        /*�����жϵ�ǰ�����Ƿ��ͷ���ȫ*/
    LevelState* current_state = new ReadyState();


    void off_car();
    void off_sun();
    void off_zombie_schedule();
    void off_plant_schedule();
    void off_bullet_schedule();
    /*������غ�������*/
    void addbackground();
    void addloadingBar();
    virtual void addcard();      /*��ͬ�ؿ����ÿ�Ƭ��ͬ���̳��������д*/
    void addlabel();
    void addshop();            /*�����̵�*/
    void addcar();
    void addmusic();
    void addshovel();
    void init_shovel();
    bool touch_shovel_began(Touch* t, Event* e);
    bool touch_shovel_end(Touch* t, Event* e);
    /*������غ�������*/
    void addexitButton();
    void init_exitButton_event();
    bool touch_exitButton_began(Touch* t, Event* e);
    bool touch_exitButton_end(Touch* t, Event* e);
    /*�˳�ѡ����غ�������*/

    /*�˵�ѡ����غ�������*/
    virtual void flush();        /*һ�󲨽�ʬ��ʱ���еĲ���*/

    /*����Ϊ��̬��ӵ�λ����*/
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
    virtual void set_level_ready() {};  /*��ɹؿ�ʱ���ڼ�¼ʤ�����*/
    void stop();
    void addzombie();    /*�������������ӽ�ʬ�ĺ��������ǵ����ӽ�ʬ�ĺ���*/
    void back_to_select();
    void setState(LevelState* state);
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void loadResoure();         /*�������о����Ա*/
    /*��ʼ����غ�������*/
    virtual void update(float dt);
    /*refectoring*/
    int getTime();
    /*��Ϸ���к�������*/
    CREATE_FUNC(Level);
};
/*�ؿ����࣬�Ե�����Ϊ������̬*/
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
/*�ؿ���*/


