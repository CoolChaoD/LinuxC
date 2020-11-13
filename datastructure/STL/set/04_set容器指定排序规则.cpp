#include <iostream>
using namespace std;
#include <set>


//set容器默认的排序是从小到大，改变其排序规则
//主要技术点： 仿函数
class MyCompare
{
  public:
    bool operator()(int v1,int v2)
    {
       return v1>v2;
    }
};
void test01(){
  set<int> s1;

  s1.insert(10);
  s1.insert(20);
  s1.insert(-10);
  s1.insert(5);

  for(set<int>::iterator it=s1.begin();it!=s1.end();it++)
  {
    cout<<*it<<" ";
  }
  cout<<endl;
  set<int,MyCompare> s2;
  s2.insert(0);
  s2.insert(-1);
  s2.insert(2);
  s2.insert(-3);
  for(set<int,MyCompare>::iterator it=s2.begin();it!=s2.end();it++)
  {
    cout<<*it<<" ";
      
  }
  cout<<endl;
}

int main(){

  test01();
  return 1;
} 
