/*
 * 快速排序
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void quickSort(int left,int right,vector<int>& arr){
        if(left>=right){
           return;// 递归结束的条件
        }
        int i=left;
        int j=right;
        int base=arr[left]; //基准数
        while(i<j){
           //取左边的数作为基准数，那么从右边开始计算
           while(i<j&&arr[j]>=base){
              j--;
           }
           while(i<j&&arr[i]>=base){
             i++;
           }
           if(i<j){
               swap(arr[i],arr[j]);
           }

        }
        //基数归为
        arr[left]=arr[i];
        arr[i]=base;

        //分别向左右递归
        quickSort(left,i-1,arr);
        quickSort(j+1,righti,arr);
}
int main(){

  

  return 1;
}
