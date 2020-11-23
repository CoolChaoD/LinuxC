//利用truncate函数拓展文件的大小
#include <stdio.h>
#include <unistd.h>

int main()
{
  int ret=truncate("test.txt",250);
  printf("ret=%d",ret);
  return 0;
}
