/*
 *函数对象（仿函数）
 函数对象在使用的时候，可以像普通函数那样调用，可以有参数 =，可以有返回值
 函数对象可以作为普通参数传递
 * */
#include  <iostream>
#include <string>
using namespace std;

//1.函数调用再使用的时候，可以像普通函数那样调用，可以有参数可以有返回值
class MyAdd
{
  public:
    int operator()(int v1,int v2)
    {
      return v1+v2;
    }
};

//2.函数对象超出普通函数的概念，函数对象可以有自己的状态·
class MyPrint
{
  public:
    MyPrint()
    {
      this->count=0;
    }
    void operator()(string test)
    {
      cout<<test<<endl;
      this->count++;
    }
    int count;//内部自己的状态

};
//函数对象可以作为参数传递
void doPrint(MyPrint &mp,string test)
{
  mp(test);
}
void test01()
{
  MyAdd add;
}
void test02()
{
  MyPrint myPrint;
  myPrint("hello world");
  myPrint("hello world");
  myPrint("hello world");
  myPrint("hello world");

  cout<<"myPrint调用的次数为："<<myPrint.count<<endl;
}
void test03()
{
  MyPrint myPrint;
  doPrint(myPrint,"Hello C++");
}
int main()
{
  //  MyAdd myadd;
  // cout<<myadd(10,10)<<endl;
  test02();
  test03();
  return 0;
}
