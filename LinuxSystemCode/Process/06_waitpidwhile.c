/*
 * 回收多个子进程
 * */
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
  //1.循环创建5个进程
  int i;
  pid_t pid,wpid;

  for(i=0;i<5;i++)
  {
    pid=fork();
    if(pid==0)
      break; 
  }

  if(i==5)
  {
    //进入父进程当中
    //2.阻塞式回收
   // while(wpid=waitpid(-1,NULL,0))
    //  printf("parent waitpid child :%d\n",wpid);
    //3. 非阻塞式回收
    while((wpid=waitpid(-1,NULL,WNOHANG))!=-1)
      if(waitpid>0)
      {
        printf("wait child %d\n",wpid);
      }else if(wpid==0)
      {
        sleep(2);
        continue;
      }
  }
  return 0;
}

