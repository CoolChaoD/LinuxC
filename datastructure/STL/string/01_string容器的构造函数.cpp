#include <iostream>
#include <string>

using namespace std;


//string 的构造函数
void test01(){
    string s1;//默认构造
    const char *str ="hello world!";
    string s2(str);
    cout<<"s2="<<s2<<endl;
    //拷贝构造
    string s3(s2);
    cout<<"s3="<<s3<<endl;
    string s4(10,'a');
    cout<<"s4="<<s4<<endl;
}
int main(){
   test01();
   return 0;
}
