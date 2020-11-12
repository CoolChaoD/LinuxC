/*
 * 第一次练习选择排序
 * */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void selectSort(vector<int>& arr){

  for(int i=0;i<arr.size()-1;i++){
    int minIndex=i;  //将第一个元素设定为最小的元素
    for(int j=i+1;j<arr.size();j++){
      if(arr[minIndex]>arr[j]){
        minIndex=j;
      }  //说明j是更小的下标
    } 
    //一轮下来后将最小的元素放在第一个
    if(minIndex!=i){
      swap(arr[minIndex],arr[i]);
    }

  }
}

int main(){
  vector<int> v={5,3,-1,2,8,9,10};
  cout<<"排序前"<<endl;
  for(vector<int>::iterator it=v.begin();it!=v.end();it++){
      cout<<*it<<" ";
  }
  cout<<endl;
  selectSort(v);
  cout<<"排序后"<<endl;
  for(vector<int>::iterator it=v.begin();it!=v.end();it++){
      cout<<*it<<" ";
  }
}
