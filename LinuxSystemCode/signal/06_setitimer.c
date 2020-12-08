/*
 * 学习使用setitimer函数
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

void myfun(int signo)
{
  printf("helloworld\n");
}
int main()
{


  struct itimerval time,oldtime;
  signal(SIGALRM,myfun);


  time.it_value.tv_sec=2;
  time.it_value.tv_usec=0; 

  time.it_interval.tv_sec=5;
  time.it_interval.tv_usec=0; 
  
  if(setitimer(ITIMER_REAL,&time,&oldtime)==-1)
  {
    perror("setitimer error");
    exit(1);

  }
  while(1);
  return 0;
}


