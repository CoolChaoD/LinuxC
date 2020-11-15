/*
 * 仿函数的返回值类型是bool数据类型称为谓词
 * operator中的参数是一个称为一元谓词
 * operator中的参数是两个称为二元谓词
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class GreaterFive
{
  public:
    bool operator()(int val)
    {
      return val>5;
    }
};

void test01()
{
  vector<int> v;
  for(int i=0;i<10;i++)
  {
    v.push_back(i);
  }
  //查找容器中有没有大于5的数字
  //GreaterFive中创建一个匿名函数对象
  vector<int>::iterator it=find_if(v.begin(),v.end(),GreaterFive());
  if(it==v.end())
  {
    cout<<"未找到"<<endl;
  }
  else
  {
    cout<<"找到了大于5的数字为:"<<*it<<endl;
  }


}

int main()
{
  test01();
  return 0;
}
