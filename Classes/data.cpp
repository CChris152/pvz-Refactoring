#include<vector>
#include "PVZ.h"
Plant* board[5][9];
std::vector<zombie*>line_1;
std::vector<zombie*>line_2;
std::vector<zombie*>line_3;
std::vector<zombie*>line_4;
std::vector<zombie*>line_5;
std::vector<sun*>all_sun;
std::vector<Bullet*>all_bullet;
car* all_car[5];
int total = 1000;    /*Ϊ����ÿ�������඼���Է������֣�ʹ��ȫ�ֱ���*/
bool level_1_ready = 1;
bool level_2_ready = 1;
/*�ؿ�������*/