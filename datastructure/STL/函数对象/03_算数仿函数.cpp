/*
 *内建函数对象 算数仿函数

 negate 一元仿函数 取反仿函数
 *
 * */
#include <iostream>
#include <functional>

using namespace std;

void test01()
{
  negate<int> n;
  cout<<n(50)<<endl;
}

void test02()
{
  plus<int> p;

  cout<<p(10,2)<<endl;
}
int main()
{
  test02();
  test01();
  return 0;
}


