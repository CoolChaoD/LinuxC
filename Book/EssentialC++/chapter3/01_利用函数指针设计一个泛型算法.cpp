#include <iostream>
#include <vector>

using namespace std;

bool less_than(int v1,int v2)
{
  return v1<v2?true:false;
}

bool greater_than(int v1,int v2)
{
  return v1>v2?true:false;
}

typedef  bool (*compare)(int,int);//定义一个函数指针
vector<int> filter(const vector<int> &v,int value,compare pred)
{
  vector<int> vRet;
  for(vector<int>::const_iterator it=v.begin();it!=v.end();it++)
  {
    if(pred(*it,value))
    {
      vRet.push_back(*it);
    }
  }

  return vRet;
}
int main()
{
  //设计一个算法找出一个列表中大于或者小于特定的数值元素
  vector<int> vTest={1,10,2,11,12,13};
  vector<int> vRet;
  vRet=filter(vTest,10,greater_than);
  cout<<"after filter:";
  for(int i=0;i<vRet.size();i++)
  {
    cout<<vRet[i]<<" ";
  }
  cout<<endl;
  return 0;
  
}
