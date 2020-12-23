//本案例用来学习输入输出迭代器
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
  istream_iterator<string> is(cin);
  istream_iterator<string> eof;  //不指定对象即为标准输入

  vector<string> text;
  copy(is,eof,text.begin());

  sort(text.begin(),text.end());

  ostream_iterator<string> os(cout," ");
  copy(text.begin(),text.end(),os);
  return 0;

}


