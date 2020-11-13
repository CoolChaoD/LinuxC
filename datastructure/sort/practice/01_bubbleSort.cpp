#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void myprint(int val){
  cout<<val<<" ";
}

void bubbleSort(vector<int>&arr){
     int flag=0;
     for(int i=0;i<arr.size()-1;i++){
        for(int j=0;j<arr.size()-1-i;j++){
          if(arr[j]>arr[j+1]){
            flag=1;
            swap(arr[j],arr[j+1]);
          }
        }  
        if(flag==0){
          //说明在某一趟遍历中没有发生交换因此可以
          break;//说明已经是有序的了
        }else{
          flag=0;
        }
        cout<<"第"<<i+1<<"轮"<<endl;
        for_each(arr.begin(),arr.end(),myprint);
        cout<<endl;
     }
}

int main(){
  vector<int> arr={1,-3,5,2,4,9,-10,1000,0};
  bubbleSort(arr);
  return 0;
}
