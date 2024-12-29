#pragma once
#include"cocos2d.h"
#include<zombie/zombie.h>
#include "ui/CocosGUI.h"
USING_NS_CC;


class Factory  //工厂基类
{
public:
	static Sprite* add_sprite(cocos2d::Node* parent,int layer);
    
    
};
class ZombieFactory:Factory  //僵尸工厂
{
    static void load_normal(zombie* zombie);
    static void load_flag(zombie* zombie);
    static void load_buckethead(zombie* zombie);
public:
    static zombie* add_zombie(double line, cocos2d::Node* parent);
    static void add_normal_zombie(double line, cocos2d::Node* parent);
    static void add_flag_zombie(double line, cocos2d::Node* parent);
    static void add_buckethead_zombie(double line, cocos2d::Node* parent);
};
