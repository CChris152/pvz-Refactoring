 #pragma once
#include"cocos2d.h"
USING_NS_CC;
class select :public cocos2d::Scene
{
	void loadResource();
	void add_background();
	void add_music();
	void back_start();
public:
	static void stop_music();
	virtual bool init();
	static cocos2d::Scene* createScene();
	~select();
	CREATE_FUNC(select);
};
