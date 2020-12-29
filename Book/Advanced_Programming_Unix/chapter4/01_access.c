/*
 *access函数用来测试访问文件的能力
 * */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


//声明一个错误处理函数
void perr_exit(const char* str)
{
  perror(str);
  exit(1);
}

int main(int argc,char *argv[])
{
  int ret;

  //判断文件是否存在
  ret=access(argv[1],F_OK);
  if(ret==0)
  {
    printf("文件存在\n");
  }else{
    printf("文件不存在\n");
    exit(0);
  }

  //判断文件是否可读
  ret=access(argv[1],R_OK);
  if(ret==0)
  {
    printf("文件可读\n");
  }else{
    printf("文件不可读\n");
  }
  
  //判断文件是否可写
  ret=access(argv[1],W_OK);
  if(ret==0)
  {
    printf("文件可写\n");
  }else{
    printf("文件不可以写\n");
  } 

  //判断文件是否可执行
  ret=access(argv[1],X_OK);
  if(ret==0)
  {
    printf("文件可执行\n");
  }else{
    printf("文件不可以执行\n");
  } 
  return 0;
}
