/*
 * 利用pipe父子进程通信实现ls | wc-l
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
  //变量声明
  pid_t pid;
  char buf[1024];
  int fd[2];
  
  int ret=pipe(fd);
  if(ret==-1)
  {
    perror("pipe error");
    exit(1);
  }
  pid=fork();
  if(pid==0)
  {
    //子进程
    //子进程关闭读端，去写入到管道中
    //fd[0] 读端 ，fd[1]写端
    close(fd[0]);
    int newfd=dup2(STDOUT_FILENO,fd[1]);
    if(newfd==-1)
    {
      perror("dup2 error");
      exit(1);
    }

    execl("ls","ls",NULL);
    perror("execlp error");
    exit(1);
  }
}

