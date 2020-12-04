#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
  int fd[2];
  pid_t pid;
  char buf[1024];
  int ret=pipe(fd);
  if(ret==-1)
  {
    perror("pipe error");
    exit(1);
  }
  //创建子进程，实现子进程向父进程发送数据
  pid=fork();
  if(pid==-1)
  {
    perror("fork error");
    exit(1);
  }else if(pid==0){
    //进入子进程
    //1.子进程关闭读端
    close(fd[0]);
    const char *senddata="hello pipe\n";
    int ret=write(fd[1],senddata,strlen(senddata));
    if(ret==-1)
    {
      perror("write error");
      exit(1);
    }
  }else if(pid>0){
    //进入父进程
    //2.父进程关闭写端
    close(fd[1]);
    int ret=read(fd[0],buf,sizeof(buf));
    if(ret==-1)
    {
      perror("read error");
      exit(1);
    }

    int ret2=write(STDOUT_FILENO,buf,ret);
    if(ret2==-1)
    {
      perror("write error");
      exit(1);
    }

  }
  return 0;
}

