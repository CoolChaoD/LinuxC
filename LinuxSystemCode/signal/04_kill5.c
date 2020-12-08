/*
 * 循环创建5个子进程，在父进程中用kill杀死任意一个子进程
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main()
{
  pid_t pid;
  int i;
  int pid_list[5];
  for(i=0;i<5;i++)
  {
    pid=fork();
    pid_list[i]=pid;
    if(pid==-1)
    {
      perror("fork error");
      exit(1);
    }
    else if(pid==0)
      break;
  }
  if(i!=5)
  {
    while(1);
  }

  
  
  if(i==5)
  {
    //进入父进程
    printf("parent,kill one childi\n");
    int n=rand()%5; //创建一个随机数
    int ret=kill(pid_list[n],SIGKILL);
    if(ret==-1)
    {
      perror("kill error");
      exit(1);
    }
    printf("kill child %d\n",pid_list[n]);
    while(1);

  }
  return 0;
}
