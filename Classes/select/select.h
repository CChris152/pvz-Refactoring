 #pragma once
#include"cocos2d.h"
USING_NS_CC;
class select :public cocos2d::Scene
{
	void loadResource();
	void add_background();
	void add_music();
	void stop_music();
	void back_start();
public:

	virtual bool init();
	static cocos2d::Scene* createScene();
	~select();
	CREATE_FUNC(select);
};
