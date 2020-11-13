#include <iostream>
#include <set>

using namespace std;


//set容器的构造和赋值
void printSet(set<int>& s){
  for(set<int>::iterator it=s.begin();it!=s.end();it++){
    cout<<*it<<" ";
  }
  cout<<endl;
}

void test01(){
  set<int> s1;
  //set容器插入的方式只有insert
  //set容器在插入的时候自动排序，set容器不允许插入重复值
  s1.insert(10);
  s1.insert(30);
  s1.insert(40);
  s1.insert(5);

  printSet(s1);



  //set容器的拷贝构造
  set<int> s2(s1);
  printSet(s2);
}

int main(){
  test01();
  return 0;
}
