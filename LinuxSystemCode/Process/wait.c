#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{

  pid_t pid,wpid;
  int status;

  pid=fork();
  if(pid==0)
  {
    //子进程
    printf("I am child,my pid is %d,I am going to sleep 10s\n",getpid());
    sleep(10);
    printf("Child is  die\n");
    return 77;
  }else if(pid>0){
    //父进程
    wpid=wait(&status);
    if(wpid==-1)
    {
      perror("wait error");
      exit(1);
    }
    printf("parent wait the %d child process\n",wpid);
    if(WIFEXITED(status))
    {
      printf("child exit with %d\n",WEXITSTATUS(status));//获取退出状态
    }
    if(WIFSIGNALED(status))
    {
      printf("child exit with siganl %d\n",WTERMSIG(status));
    }


  }else{
    perror("fork error");
    exit(1);
  }
  return 0;
}
