#ifndef _SPEECHMANGER_H_
#define _SPEECHMANGER_H_
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"

//设计演讲管理者类
class SpeechManger
{
  public:
    //构造函数
    SpeechManger();


    //菜单功能
    void show_Menu();

    //退出菜单
    void exitSystem();
    //析构函数
    ~SpeechManger();
    
    //清空容器
    void initSpeech();

    //创建12名选手
    void createSpeaker();

    //成员属性
    //保存第一轮比赛选手编号容器
    vector<int> v1;
    //第一轮 晋级选手编号容器
    vector<int> v2;

    //胜出前三名选手编号容器
    vector<int> vVectory;

    //存放具体编号以及选手的容器
    map<int,Speaker>m_Speaker;

    //比赛轮数
    int m_Index;
};








#endif
