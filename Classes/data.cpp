#include<vector>
#include "PVZ.h"
Plant* board[5][9];
std::vector<Zombie*>line_1;
std::vector<Zombie*>line_2;
std::vector<Zombie*>line_3;
std::vector<Zombie*>line_4;
std::vector<Zombie*>line_5;
std::vector<sun*>sunPool;
std::vector<Bullet*>all_bullet;
car* all_car[5];
int total = 1000;    /*为了让每个阳光类都可以访问数字，使用全局变量*/
bool level_1_ready = 1;
bool level_2_ready = 1;
/*关卡完成情况*/