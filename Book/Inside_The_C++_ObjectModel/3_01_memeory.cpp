//本案例用来分析C++类的内存布局
#include <iostream>


using namespace std;

//静态数据成员
class Sheep
{
  public:
    static int m_a;
};
int Sheep::m_a=10;

void test01()
{
  //查看静态数据成员是否属于一个类
  Sheep s1;
  cout<<sizeof(s1)<<endl;
  cout<<"m_a的大小为"<<s1.m_a<<endl;
}

//2.内存对齐


class Dog
{
  public:
   
    int a;
    short c;
    char b; 
};

void test02()
{
  Dog dog;
  cout<<sizeof(dog)<<endl;
}
int main()
{
  //test01();
  test02();
  return 0;
}

