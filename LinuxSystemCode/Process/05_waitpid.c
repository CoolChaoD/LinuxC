#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main()
{
  pid_t wpid,pid,tmid;
  int status,i;
  for(i=0;i<5;i++)
  {
    pid=fork();
    if(pid==0){
      break;
    }
    if(i==2)
    {
      tmid=pid;
      printf("pid=%d\n",tmid);
    }
 }
  if(i==5)
  { 
    // sleep(5);
     //父进程
     wpid=waitpid(tmid,&status,WNOHANG);
     if(wpid==-1)
     {
       perror("wait error");
       exit(1);
     }
     printf("I am parent ,wait a child finish:%d\n",wpid);
  }
  return 0;
}

