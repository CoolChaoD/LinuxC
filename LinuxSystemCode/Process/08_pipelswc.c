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
    dup2(fd[1],STDOUT_FILENO); //将原本要输入到屏幕上的数据输入到管道中
    execlp("ls","ls",NULL);
    perror("execlp error");
    exit(1);
  }else if(pid>0){
     //父进程
     //父进程读取管道的内容，然后将fd[0]绑定到标准输入
     //以下代码为了看起来简洁省去了返回值的检查
     close(fd[1]); //关闭文件的写端，父进程要读取
     dup2(fd[0],STDIN_FILENO);
     execlp("wc","wc","-l",NULL); //wc指令输入的内容来自显示屏
     
  }
  return 0;
}

