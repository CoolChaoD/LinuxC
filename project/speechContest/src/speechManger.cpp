#include "speechManger.h" 
#include <algorithm>
#include <unistd.h>

//构造函数
SpeechManger::SpeechManger()
{
  //初始化容器和属性
  this->initSpeech();
  //构造12名选手
  this->createSpeaker();

}

//菜单功能
void SpeechManger::show_Menu()
{
  cout<<"**************************************"<<endl;
  cout<<"******  欢迎参加演讲比赛  ************"<<endl;
  cout<<"******  1.开始演讲比赛    ************"<<endl;
  cout<<"******  2.查看往届记录    ************"<<endl;
  cout<<"******  3.清空比赛记录    ************"<<endl;
  cout<<"******  0.退出比赛程序    ************"<<endl;
  cout<<"**************************************"<<endl;
  cout<<endl;

}
//退出菜单
void SpeechManger::exitSystem()
{
  cout<<"欢迎下次使用"<<endl;
  exit(1);

}


//清空容器
void SpeechManger::initSpeech()
{
  //容器置空
  this->v1.clear();
  this->v2.clear();
  this->vVectory.clear();
  this->m_Speaker.clear();

  //初始化比赛的轮数
  this->m_Index=1;
}
//创建12名选手
void SpeechManger::createSpeaker()
{
  string nameSeed={"ABCDEFGHIJKL"};
  for(int i=0;i<nameSeed.size();i++)
  {
    string name="选手";
    name+=nameSeed[i];
    //创建具体的选手
    Speaker sp; //创建一个选手
    sp.m_Name=name;
    for(int j=0;j<2;j++)
    {
      sp.m_Score[j]=0;
    }
    //创建选手编号,并存放到v1容器当中
    this->v1.push_back(i+10001);

    //选手编号以及对应的选手 放入到map容器当中 
    this->m_Speaker.insert(make_pair(i+10001,sp));




  }
}
//开始比赛 比赛的整个流程控制函数
void SpeechManger::startSpeech()
{
   //第一轮开始比赛
   
  //1.抽签
  this->speechDraw();
   

  //2.比赛
  //3.显示晋级结果
  //第二轮开始比赛
  //1.抽签
  //2.比赛
  //3.显示最终结果
  //4.保存分数到文件中
}
//抽签
void SpeechManger:: speechDraw()
{
  cout<<"第<<"<<this->m_Index<<">>轮比赛选手正在抽签"<<endl;
  cout<<"-------------------------------"<<endl;
  cout<<"抽签后的顺序如下："<<endl;
  if(this->m_Index==1)
  {
    //第一轮比赛
    random_shuffle(v1.begin(),v1.end());
    for(vector<int>::iterator it=v1.begin();it!=v1.end();it++)
    {
      cout<<*it<<endl;
    }
    cout<<endl;

  }else
  {
    //第二轮比赛
    random_shuffle(v2.begin(),v2.end());
    for(vector<int>::iterator it=v2.begin();it!=v2.end();it++)
    {
      cout<<*it<<endl;
    }
    cout<<endl;
    
  }
  cout<<"------------------------"<<endl;
  pause();
  cout<<endl;
}
//析构函数
SpeechManger::~SpeechManger()
{

}
