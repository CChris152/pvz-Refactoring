#pragma once
#include"cocos2d.h"
#include"zombie/zombie.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
// 工厂接口

class Factory
{
public:
    Sprite* createSprite(Sprite* outside_sprite)
    {
    };
    ~Factory(){}
};

