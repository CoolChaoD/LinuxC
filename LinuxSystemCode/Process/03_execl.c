#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
  pid_t pid=fork();
  if(pid==-1)
  {
    perror("fork error");
    exit(1);
  }else if(pid==0){ //子进程
    execl("./execl_test","./execl_test",NULL);
    perror("exec error");
    exit(1);
  }else if(pid>0){ //父进程
    sleep(1);
    printf("I am the father，my id id %d\n",getpid());

  }
  return 0;
}
