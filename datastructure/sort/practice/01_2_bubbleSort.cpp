//练习冒泡排序
#include <iostream>
#include <vector>
#include <algorithm>

using  namespace std;

void myPrint(int val){
  cout<<val<<" ";
}

void bubbleSort(vector<int>& arr){
  for(int i=0;i<arr.size()-1;i++)
  {
    for(int j=0;j<arr.size()-1-i;j++)
    {
      if(arr[j]>arr[j+1])
      {
        swap(arr[j],arr[j+1]);
      }
    }
    cout<<"第"<<i+1<<"轮"<<endl;
    for_each(arr.begin(),arr.end(),myPrint);
    cout<<endl;
  }
}

int main()
{
  vector<int> arr={12,19,-19,8,7,2};
  bubbleSort(arr);
  return 0;

}
