//本案例用于验证文件读写使用同一个位置指针
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void sys_error(const char*str)
{
  perror("str");
  exit(1);
}

int main()
{
  int  n;  //接收返回字节数
  char ch;//定义一个字节用来存储接收的数据
  char *str="hello world\n";
  //1.打开一个文件并向里面写入该字符串
  int fd=open("lseek.txt",O_RDWR|O_CREAT,0644);
  if(fd==-1)
  {
    sys_error("open error");
  }
  write(fd,str,strlen(str)); //向文件内部写入字符串
  lseek(fd,0,SEEK_SET); //将文件指针放到首位
  while((n=read(fd,&ch,1)))
  {
    if(n<0)
    {
      sys_error("read error");
    }
    write(STDOUT_FILENO,&ch,n); //文件按照字节输出
  }
  close(fd);
  return 0;
}
