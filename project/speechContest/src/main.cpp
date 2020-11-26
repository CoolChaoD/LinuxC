//主函数
#include <iostream>
#include "speechManger.h"
#include <iostream>  
#include <string>

using namespace std;

int  main()
{
  //创建一个管理类的象
  SpeechManger sm;

  //测试12名选手的创建
  for(map<int,Speaker>::iterator it=sm.m_Speaker.begin();it!=sm.m_Speaker.end();it++)
  {
    cout<<"编号:"<<it->first<<" 姓名:"<<it->second.m_Name<<" 第一轮得分："<<it->second.m_Score[0]<<endl;
    
  }

  cout<<"请输入您的选择："<<endl;
  int choice =0; //用于存储用户的输入
  while(true)
  {

  //展示界面
  sm.show_Menu();

  cin>>choice;
  switch(choice)
  {
    case 1: //开始比赛
      break;
    case 2: //查看往届记录
      break;
    case 3: //清空比赛记录
      break;
    case 0: //退出比赛系统
      sm.exitSystem();
      break;
    default: //清屏
      system("reset");
      break;
  }
  }
  return 0;
}
