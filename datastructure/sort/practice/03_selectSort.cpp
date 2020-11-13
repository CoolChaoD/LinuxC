#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void selectSort(vector<int>& arr){
    for(int i=0;i<arr.size()-1;i++){
        int minIndex=i;//选择i作为最小的下标
        for(int j=i+1;j<arr.size();j++){
          if(arr[minIndex]>arr[j]){
                minIndex=j;
          }
          if(minIndex!=i){
            swap(arr[minIndex],arr[i]);
          }
        }
    }
 
}


void myPrint(int val){
    cout<<val<<" ";
}
int main(){

  vector<int> arr={-10,5,6,2,3,9};
  selectSort(arr);
  for_each(arr.begin(),arr.end(),myPrint);
  return 0;

}

