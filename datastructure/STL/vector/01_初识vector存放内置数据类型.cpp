#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void myPrint(int val){
  cout<<val<<" ";

}

void test01(){
  //创建一个vector容器对象，并通过模板参数指定容器中存放的数据类型
  vector<int> v;
  //向容器中放数据
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  //每一个容器都有一个自己的迭代器，迭代器用来遍历容器中存放的数据
  //v.begin()返回迭代器，这个迭代器指向容器中的第一个数据
  //v.end()返回迭代器，这个迭代器指向容器的第一个数据
  //vector<int>::iterator 拿到vector<int>  这种容器的迭代器类型
  vector<int>::iterator pBegin=v.begin();
  vector<int>::iterator pEnd=v.end();    //注意begin指向容器元素的第一个元素，但是end指向这个元素的下一个位置

  //第一种遍历方式
  cout<<"第一种遍历方式"<<endl;
  while(pBegin!=pEnd){
    cout<<*pBegin<<" ";
    pBegin++;
  }
  cout<<endl;

  //第二种遍历方式
  cout<<"第二种遍历方式"<<endl;
  for(vector<int>::iterator it=v.begin();it!=v.end();it++){
    cout<<*it<<" ";
  }
  cout<<endl;

  //第三种遍历方式
  for_each(v.begin(),v.end(),myPrint);
  cout<<endl;
}

int main(){
  test01();
  return 0;
}
