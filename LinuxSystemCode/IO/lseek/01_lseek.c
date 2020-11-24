#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

/*
 * 本案例用于验证文件的读和写是使用同一个位置偏移量的 
 */
int main()
{
  int fd,n;
  char msg[]="It is a test for lessk\n";
  char ch;

  fd=open("lessk.txt",O_RDWR|O_CREAT,0644); //打开一个文件获取文件描述符
  if(fd<0)
  {
    perror("open lessk.txt error");
    exit(1);
  }

  write(fd,msg,strlen(msg));
  lseek(fd,0,SEEK_SET); //修改文件读写指针
  while((n=read(fd,&ch,1)))
  {
    if(n<0)
    {
      perror("read error");
      exit(1);
    }
    write(STDOUT_FILENO,&ch,n);  //将文件的内容按照字节输出
  }
  close(fd);
  return 0;
}



