#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

//本案例用于练习函数对象适配器以及，泛型编程

using namespace std;

template<class InputItertor,class OutputIterator,class ElemType,class Comp>
OutputIterator  filter(InputItertor first,InputItertor last,OutputIterator at,const ElemType &val, Comp Pred)
{
  while((first=find_if(first,last,bind2nd(Pred,val)))!=last)
  {
      //观察情况
      cout<<"found value:"<<*first<<endl;
      *at++=*first++;
  }
  return at;
}
int main()
{
  const int elem_size=8;

  int ia[elem_size]={12,8,43,0,6,21,3,7};
  int ia2[elem_size];
  vector<int> ivec(ia,ia+elem_size);
  vector<int> ivec2(elem_size);
  cout<<"filter integer array for values less than 8\n";
  filter(ia,ia+elem_size,ia2,elem_size,less<int>());
  cout<<"filter integer vector for values greater than 8\n";
  filter(ivec.begin(),ivec.end(),ivec2.begin(),elem_size,greater<int>());

}
