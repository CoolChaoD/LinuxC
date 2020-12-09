/*
 *学习使用信号集操作函数
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void print_set(sigset_t *set)
{
  int i;
  for(i=1;i<32;i++)
  {
    if(sigismember(set,i))
    {
      putchar('1');
    }
    else
      putchar('0');
  }
}

int main() 
{
  sigset_t set,old_set,pedset;

  int ret=0;

  sigemptyset(&set);//清空set
  sigaddset(&set,SIGINT);

  ret=sigprocmask(SIG_BLOCK,&set,&old_set); //设置屏蔽信号
  if(ret==-1)
  {
    perror("sigprocmask error");
    exit(1);
  }
  ret=sigpending(&pedset);
  if(ret==-1)
  {
    perror("sigpending error");
  }
  print_set(&pedset);
  while(1);
  return 0;
}
