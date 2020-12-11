#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ULONGLONG_MAX （pow(2, 64) - 1）

//循环创建5个子线程
void *tfn(void *arg)
{
  printf("-- thread:pid=%d,tid=%lu\n",getpid(),pthread_self());
  return NULL;
}

int main()
{
  int i;
  pthread_t tid;
  int ret;

  for(i=0;i<5;i++){
    ret=pthread_create(&tid,NULL,tfn,NULL); //创建一个先后线程
    if(ret!=0)
    {
      perror("pthread_create error");
      exit(1);
    }
  }
  sleep(1);
  return 0;

}
