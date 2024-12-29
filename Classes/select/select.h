 #pragma once
#include"cocos2d.h"
USING_NS_CC;
class select :public cocos2d::Scene
{
	Sprite* Level_1;
	Sprite* Level_2;
	Sprite* Level_3;
	Sprite* backButton;
public:
	void loadResource();
	void add_background();
	void add_music();
	void stop_music();

	void add_Level_1();
	void init_Level_1_event();
	bool touch_Level_1_began(Touch* t, Event* e);
	bool touch_Level_1_end(Touch* t, Event* e);

	void add_Level_2();
	void init_Level_2_event();
	bool touch_Level_2_began(Touch* t, Event* e);
	bool touch_Level_2_end(Touch* t, Event* e);

	void add_Level_3();
	void init_Level_3_event();
	bool touch_Level_3_began(Touch* t, Event* e);
	bool touch_Level_3_end(Touch* t, Event* e);

	void add_backButton();
	void init_backButton_event();
	bool touch_backButton_began(Touch* t, Event* e);
	bool touch_backButton_end(Touch* t, Event* e);
	void back_start();
	virtual bool init();
	static cocos2d::Scene* createScene();
	~select();
	CREATE_FUNC(select);
};
