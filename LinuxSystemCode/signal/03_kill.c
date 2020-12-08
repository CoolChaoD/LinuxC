#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

//利用kill函数在子进程中杀死父进程
int main()
{
  pid_t pid;
  pid=fork();//创建一个子进程
  if(pid<0)
  {
    perror("fork error");
    exit(1);
  }else if(pid>0){
    //父进程
    printf("parent ,pid=%d\n",getpid());
    while(1);
  }else if(pid==0){
    //子进程
    printf("child,  pid=%d\n",getpid());
    sleep(2);
    kill(getppid(),SIGBUS);
  }
  return 0;


}

