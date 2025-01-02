#pragma once
#include <unordered_map>
#include<zombie/zombie.h>
#include"cocos2d.h"
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
class PlantFactory :Factory
{
    static Sprite* add_plant(int row, int line, cocos2d::Node* parent);
    static void load(int row,int line,Plant* plant);
public:
    static void add_bulletShooter(int row, int line, cocos2d::Node* parent);
    static void add_sunflower(int row, int line, cocos2d::Node* parent);
    static void add_nut(int row, int line, cocos2d::Node* parent);
    static void add_potatoMine(int row, int line, cocos2d::Node* parent);
};
