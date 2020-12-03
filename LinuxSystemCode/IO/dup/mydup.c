/*
 * dup与dup2
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char*argv[])
{ 
   //dup创建一个文件描述符的副本，但是新的fd(file descriptor)不可以被指定
   //默认为最小的没有被使用的文件描述符
   //dup2与dup相同可以创建一个文件描述符的副本，并且可以指定具体的文件描述符
   //int dup(int oldfd);
   //int dup2(int oldfd, int newfd);
   //下面以一个具体的案例来讲解将输出到屏幕的内容重定向输出的文件中

  int fd=open("./duptest.txt",O_RDWR);
  if(fd==-1)
  {
    perror("open error\n");
  }

  int newfd=dup2(fd,STDOUT_FILENO);//将文件描述符STDOUT_FIEN重定向到fd中，这样输出到屏幕的内容就会写入fd指向的文件中
  if(newfd==-1)
  {
    perror("dup2 error\n");
  }

  printf("------输入到屏幕------\n");

  close(fd);
  return 0;

}

