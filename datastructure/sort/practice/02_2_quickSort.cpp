#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void quickSort(int left, int right,vector<int>& arr)
{
  if(left>=right)
  {
    return; //递归结束的条件
  }

  int i=left;
  int j=right;
  int base=arr[i]; //取最左边的数作为基准数
  while(i<j)
  {
    while(i<j&&arr[j]>=base)
    {
      j--;
    }
    while(i<j&&arr[i]<=base)
    {
      i++;
    }
    if(i<j)
    {
      swap(arr[i],arr[j]);
    }
  }
  //基准数归位
  arr[left]=arr[i];
  arr[i]=base;

  //递归
  quickSort(left,i-1,arr);
  quickSort(j+1,right,arr);
}
void myPrint(int val)
{
     cout<<val<<" ";
}



int main()
{
  vector<int> arr={3,2,-1,6,7,10};
  quickSort(0,arr.size()-1,arr);
  for_each(arr.begin(),arr.end(),myPrint);
  return 0;
}

