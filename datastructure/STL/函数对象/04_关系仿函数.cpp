#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

//内建函数对象——关系仿函数
//大于 greater

void test01()
{
    vector<int> v={1,90,-10,29,39,7};
    sort(v.begin(),v.end(),greater<int>());
    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
    {
      cout<<*it<<" ";
    }
}

int main()
{
  test01();
  return 0;
}
