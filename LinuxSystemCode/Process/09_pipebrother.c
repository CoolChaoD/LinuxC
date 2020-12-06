/*
 * 利用管道实现兄弟进程之间的通信
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
  pid_t pid;
  int fd[2],i;
  char buf[1024];

  //创建管道
  int ret= pipe(fd);
  if(ret==-1)
  {
    perror("pipe error");
    exit(1);
  }
  for(i=0;i<2;i++)  //父进程出口
  {
    pid=fork();
    if(pid==-1)
    {
      perror("fork error");
      exit(1);
    }
    if(pid==0)  //子进程出口
      break;
     
  }
  if(i==2)
  {
    //父进程
    //父进程需要关闭读端和写端并且需要回收两个子进程
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
  }
  else if(i==0){
    //第一个子进程负责写
    //关闭读端
    close(fd[0]);
    const char *str="hello brother\n";
    int ret= write(fd[1],str,strlen(str));
    if(ret==-1)
    {
      perror("write error");
      exit(1);
    }
    close(fd[1]);
  }else if(i==1){
    //第二个进程负责读
    //关闭写端
    close(fd[1]);
    int ret=read(fd[0],buf,sizeof(buf));
    if(ret==-1)
    {
      perror("read error");
      exit(1);
    }
    write(STDOUT_FILENO,buf,ret);
    close(fd[0]);
  }
  return 0;
}
