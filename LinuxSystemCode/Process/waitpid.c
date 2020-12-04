#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main()
{
  pid_t wpid pid,tmid;
  int status,i;
  for(i=0;i<5;i++)
  {
    pid=fork();
    if(i==2)
    {
      tmid=pid;
    }
    if(pid==0) //如果是子进程，那么就终止不执行fork
      break; 
 }
  if(i==5)
  { 
     sleep(5);
     //父进程
     wpid=waitpid(tmid,&status,WNOHANG);
     if(wpid==-1)
     {
       perror("wait error");
       exit(1);
     }


  }
}

