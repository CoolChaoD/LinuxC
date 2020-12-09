#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void sys_err(const char *str)
{
  perror(str);
  exit(1);
}

void catch_child(int signo)
{
  pid_t wpid;
  int status;

  while((wpid=wait(NULL))!=-1)
  {
    if(WIFEXITED(status))
      printf("-------------catch_child id %d,ret=%d\n",wpid,WIFEXITED(status));
  }
  return ;
}
int main()
{
  pid_t pid;
  //为了防止在注册函数调用过程中有子进程死亡，可以先设置阻塞将SIGCHILD信号设置成阻塞，这样就算有信号来了也是未决状态
  //等sigaction函数创建完成后解除阻塞
  sigset_t set,oldset; //设置自定义的阻塞信号集
  sigaddset(&set,SIGCHLD); //将sigchild信号设置成阻塞信号
  int ret=sigprocmask(SIG_BLOCK,&set,&oldset);
  if(ret==-1)
  {
    perror("sigprocmask error");
    exit(1);
  }
  int i;
  for(i=0;i<10;i++)
  {
    pid=fork();
    if(pid==0)
      break;
  }  

  if(i==10)
  {
    //注册一个函数用来回收子进程,注册函数写在父进程中
    struct sigaction act;
    act.sa_handler=catch_child;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD,&act,NULL);

    //sigaction函数创建完毕，这时候就可以解除阻塞了
    ret=sigprocmask(SIG_UNBLOCK,&set,&oldset);
    if(ret==-1)
    {
      perror("sigprocmask error");
      exit(1);
    }


    printf("I am parent,pid=%d\n",getpid());
    while(1);
  }else{
    //进入子进程，每一个子进程中的i值都是不相同的
    printf("I am child pid=%d\n",getpid());
    return i;
  }
  return 0;

}
