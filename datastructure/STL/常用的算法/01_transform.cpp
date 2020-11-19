//常用的遍历算法transform 
//需要提前为目标容器开辟好空间
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>


using namespace std;

class Transform
{
  public:
    int operator()(int v)
    {
      return v;
    }
};
class MyPrint
{
   public:
     void operator()(int val)
     {
       cout<<val<<" ";
     }
};
void test01()
{

  vector<int> v={3,4,20,0,1,-2};
  vector<int> vTarget;
  vTarget.resize(10);
  transform(v.begin(),v.end(),vTarget.begin(),Transform());
  for_each(vTarget.begin(),vTarget.end(),MyPrint());
  cout<<endl;

}

int main()
{
  test01();
  return 0;
}

