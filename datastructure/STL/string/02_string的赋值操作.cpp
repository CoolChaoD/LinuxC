#include <iostream>
#include <string>

using namespace std;

void test01(){
    string str1;
    str1="hello world";
    cout<<"str1="<<str1<<endl;


    string str4;
    str4.assign("hello c++!");
    cout<<"str4="<<str4<<endl;

    string str5;
    str5.assign("hello c++",3);
    cout<<"str5="<<str5<<endl;

    string str6;
    str6.assign(str5);
    cout<<"str6="<<str6<<endl;

    string str7;
    str7.assign(10,'w');
    cout<<"str7="<<str7<<endl;
}

int main(){

  test01();
  return 0;
}
