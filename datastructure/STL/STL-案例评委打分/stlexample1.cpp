#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
/*
 * 有5名选手：选手ABCDE,10个评委分别对每一名选手打分，去除最高分和最低分，取平均分 
 */


class Person
{
  public:
    Person(string name,int score)
    {
      this->m_Name=name;
      this->m_Score=score;

    }

    string m_Name;
    int  m_Score; 
};


void createPerson(vector<Person>& v)
{
  string nameSeed="ABCDE";
  for(int i=0;i<5;i++)
  {
    string name="选手";
    name+=nameSeed[i];
    int score=0;
    Person p(name,score);
    //将Person创建的对象存放到容器中
    v.push_back(p);
  }
}
void setScore(vector<Person>& v)
{

  for(vector<Person>::iterator it=v.begin();it!=v.end();it++)
  {
    //将评委的打分放入到deque容器中
    deque<int> d;
    for(int i=0;i<10;i++)
    {
      int score=rand()%41+60;
      d.push_back(score);
    }
    //对打分进项排序
    sort(d.begin(),d.end());
    //去除最高分和最低分
    d.pop_back();//remove the end value
    d.pop_front();//remove the front value

    //average score
    int sum=0;
      for(deque<int>::iterator dit=d.begin();dit!=d.end();dit++)
      {
        sum+=*dit; //accumulate the score of every Person

      }
    int avg=sum/d.size();
    it->m_Score=avg;//将平均分赋给选手
  }

}
void showScore(vector<Person>& v)
{
  for(vector<Person>::iterator it=v.begin();it!=v.end();it++)
  {
    cout<<"姓名："<<(*it).m_Name<<"得分： "<<(*it).m_Score<<endl;
  }

}
int main()
{
  //设置随机数种子
  srand((unsigned int)time(NULL));
  //1.创建5名选手
  vector<Person> v;   //存放5名选手的容器
  createPerson(v);
  
  //2.给5名选手打分
  setScore(v);
  //显示最后得分
  showScore(v);
  return 0;
}
