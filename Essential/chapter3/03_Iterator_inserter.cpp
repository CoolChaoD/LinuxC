/*
 * 本案例主要学习函数对象适配器和insertIterator
 * 以及泛型算法的设计
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

  template<class InputIterator,class OutputIterator,class ElemType,class Comp>
OutputIterator filter(InputIterator first,InputIterator last,OutputIterator at,const ElemType &val,Comp pred)
{
  while((first=find_if(first,last,bind2nd(pred,val)))!=last) //函数对象适配器将pred的第二个参数绑定到val即自己需要传入的数据
  {
    //观察找到数据的情形
    cout<<"found value: "<<*first<<endl;
    *at++=*first++;//递增运算符的优先级要高于指针运算符

  }
  return at;

}

int main()
{
  const int elem_size=8;
  int ia[elem_size]={12,8,43,0,6,21,3,7};
  vector<int> ivec(ia,ia+elem_size);
  //内置数组不支持insert_iterator
  int ia2[elem_size];
  vector<int> ivec2;

  cout<<"filtering integer vector values greater than 8\n";
  filter(ivec.begin(),ivec.end(),back_inserter(ivec2),21,greater<int>());
  cout<<"filtering integer array values less than 8\n";
  filter(ia,ia+elem_size,ia2,21,less<int>());
  return 0;
}
