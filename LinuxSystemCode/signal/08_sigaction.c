/*
 * 注册一个信号捕捉函数
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void myfun(int signo)
{
  printf("catch you\n");
}
int main()
{

  //注册一个信号捕捉函数
  struct sigaction act,oldact;

  act.sa_flags=0;
  act.sa_handler=myfun;
  sigemptyset(&(act.sa_mask));
  int ret=sigaction(SIGINT,&act,&oldact);

  while(1);
  return 0;
}

