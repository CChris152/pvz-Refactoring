#include<vector>
#include "PVZ.h"
plant* board[5][9];
std::vector<zombie*>line_1;
std::vector<zombie*>line_2;
std::vector<zombie*>line_3;
std::vector<zombie*>line_4;
std::vector<zombie*>line_5;
std::vector<bullet*>all_bullet;   /*单纯用于存储所有的子弹，方便释放内存和关闭定时器*/
std::vector<sun*>all_sun;
car* all_car[5];
int total = 0;    /*为了让每个阳光类都可以访问数字，使用全局变量*/
bool level_1_ready = 0;
bool level_2_ready = 0;
/*关卡完成情况*/