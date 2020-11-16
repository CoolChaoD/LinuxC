#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void selectSort(vector<int>& arr)
{
  for(int i=0;i<arr.size()-1;i++)
  {
    int minIndex=i;//选择第一个数作为最小值
    for(int j=i+1;j<arr.size();j++)
    {
      if(arr[minIndex]>arr[j])
      {
        //说明有比我们还小的数值，保存好下标
        minIndex=j;
      }
    }
    //一轮下来后第一个位置应该是保存最小数才对
    if(minIndex!=i)
    {
      swap(arr[minIndex],arr[i]);
    }
  }
}
void myPrint(int val)
{
  cout<<val<<" ";
}
int main()
{
  vector<int> arr={4,2,1,9,3,10};
  selectSort(arr);
  for(vector<int>::iterator it=arr.begin();it!=arr.end();it++)
  {
    cout<<*it<<" ";
  }
  cout<<endl;
  return 0;
}
