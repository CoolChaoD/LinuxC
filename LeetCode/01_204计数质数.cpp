//版本1，最低端的暴力解法
#include <iostream>
#include <ctime>
#include <chrono> //计算时间

using namespace std;

int countPrime(int n)
{
  int count=0;
  for(int i=2;i<n;i++)
  {
    bool flag=true;
    for(int j=2;j<=i/2;j++)
    {
      if(i%j==0)
      {
        flag=false;
         break;
      }
    }

    if(flag)
    {
      count++;
    }
  }
  return count;
}
int main()
{

  auto start =chrono::steady_clock::now();
  int n=10000;
  int count=countPrime(n);
  auto end  =chrono::steady_clock::now();
  chrono::duration<double,micro> elapsed =end-start; 
  cout<<"time: "<<elapsed.count()<<"us"<<endl;
  cout<<count<<endl;
  return 0;
}
