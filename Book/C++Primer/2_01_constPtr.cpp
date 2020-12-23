/*
 * 本代码用来测试常量指针与指针常量
 */

#include  <iostream>

using namespace std;


void test01()
{
  //常量指针，const直接修饰指针，指针不能修改也就是说可以通过指针修改它所指向的值，但是不可以将这个指针指向一个新的变量
  int a=10;
  int b=20;
  int *const ptr=&a;
//  ptr=&b;   不能修改ptr的指向
  cout<<(*ptr)++<<endl;
  cout<<"a的值"<<a<<endl;
}
int main()
{
  const int a=10;
  const int b=20;
  const int *ptr=&a; //指向常量的指针，常量的值不可以改变,不能通过指针的去修改这个常量
  ptr=&b; //但是这个指针不是常量，可以修改
  cout<<*ptr;

  test01();
  return 0;

}
