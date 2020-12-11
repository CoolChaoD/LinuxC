#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void *tfn(void *arg)
{
  printf("thraed: pid=%d,tid=%lu\n",getpid(),pthread_self());
  return NULL;
}


int main()
{
  pthread_t tid; //创建一个线程号变量
  printf("main: pid=%d,tid=%lu\n",getpid(),pthread_self());
  int ret=pthread_create(&tid,NULL,tfn,NULL);
  if(ret!=0)
  {
    perror("pthread_create error");
  }
  sleep(1);
  return 0;
}
