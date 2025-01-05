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
    /*�˳�ѡ����غ�������*/

    /*�˵�ѡ����غ�������*/

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
    template <typename T>
    void off_schedule(std::vector<T*>& vec);
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
/*�ؿ���*/


