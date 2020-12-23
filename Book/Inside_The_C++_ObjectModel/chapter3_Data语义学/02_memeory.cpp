//本函数用来验证pragma pack()的作用
#include <iostream>

#pragma pack(1)
using namespace std;

class Dog
{
  public:
    char b;
    int a;
    short c;

};


int main()
{

  Dog dog; //创建一个dog对象
  cout<<sizeof(dog)<<endl;
  return 0;
}

