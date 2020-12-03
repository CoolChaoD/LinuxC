#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sys_error(const char *str)
{
  perror(str);
  exit(1);
}

void sig_catch(int signo)
{
  if(signo==SIGINT)
    printf("catch you!%d\n",signo);
  else if(signo==SIGQUIT)
  {
    printf("------catch you!%d\n",signo);

  }
}
int main(int argc,char *argv[])
{
  struct sigaction act, oldact;

  act.sa_handler=sig_catch;  //设置回调函数
  sigemptyset(&(act.sa_mask));  //清空sa_mask屏蔽字，只有在sig_catch工作的时候才有效
  act.sa_flags=0;  //默认值

  int ret=sigaction(SIGINT,&act,&oldact); //注册捕捉函数
  if(ret==-1)
  {
    sys_error("sigaction error");
  }
  ret=sigaction(SIGQUIT,&act,&oldact); //注册信号捕捉机
  if(ret==-1)
  {
    sys_error("sigaction error");
  }
  while(1);
  return 0;

}




