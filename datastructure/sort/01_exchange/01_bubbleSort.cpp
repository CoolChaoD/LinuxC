#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

void myprint(int val){
  cout<<val<<" ";
}




void bubbleSort(vector<int>& arr){
    // int flag=0;
     for(int i=0;i<arr.size()-1;i++){
         for(int j=0;j<arr.size()-i-1;j++){
            if(arr[j]>arr[j+1]){
      //          flag=1;
                swap(arr[j],arr[j+1]); // 交换，将最大的数放在最后
                   
            }
         }
        // if(flag==0){
           // break; //说明在一轮中没有发生交换已经是有序的了
        // }else{
         //    flag=0;
        // }
         cout<<"第"<<i+1<<"轮"<<endl;
         for_each(arr.begin(),arr.end(),myprint);
         cout<<endl;
     }

}

int main(){

  vector<int> arr={3,4,10,-9,20};
  bubbleSort(arr);
  
//  for_each(arr.begin(),arr.end(),myprint); //利用回调的技术打印
  return 0;
}
