#pragma once
class Level;
class LevelState  // ״̬�ӿ�
{
public:
    virtual void handle(Level* level) = 0;
};
class ReadyState :public LevelState // ׼���׶�
{
public:
    void handle(Level* level) override;
};

class GamingState :public LevelState
{
    int sun_interval = 5 * 60;
    int zombie_interval = 10 * 60;
    int per = 50;  //���ɸ���
    bool judge_fail();
    void add_sun(Level* level);
public:
    void handle(Level* level) override;
};
class FlushState :public LevelState
{
    int num_1 = 0;
    int num_2 = 0;
    int num_3 = 0;
    int num_4 = 0;
    int num_5 = 0;
    /*�������ڼ�¼��ǰ���ɵĽ�ʬ�����ϵķֲ����ܲ�������̫��ȫ������һ���ˣ�ǿ�е���һ��*/
    int Buckethead_num = 6;        /*��ͨ��ʬ����*/
    int flush_time = 3000;
public:
    void handle(Level* level) override;
};

class FailState :public LevelState
{
public:
    void handle(Level* level) override;
};
class WinState :public LevelState
{
    bool is_play = false;
    int win_time = 280;
    void back_to_select();
    void stop_music();
public:
    void handle(Level* level) override;
};
