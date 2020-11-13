#include <iostream>
#include <set>

using namespace std;

class Person{
  public:
   Person(string name,int age){
     this->m_Name=name;
     this->m_Age=age;


   }
   string m_Name;
   int m_Age;

};

class comparePerson{
    public:
      //按照年龄降序
      bool operator()(const Person& p1,const Person& p2)
      {
        return p1.m_Age<p2.m_Age;
      }
};

void test01(){
  set<Person,comparePerson> s;
  //创建Person对象
  Person p1("张飞",24);
  Person p2("关羽",19);
  Person p3("张飞",26);
  Person p4("赵云",28);

  s.insert(p1);
  s.insert(p2);
  s.insert(p3);
  s.insert(p4);

  for(set<Person,comparePerson>::iterator it=s.begin();it!=s.end();it++)
  {
    cout<<"姓名： "<<it->m_Name<<" 年龄： "<<it->m_Age<<endl;
  }

}
int main(){
  test01();
  return 0;
}
