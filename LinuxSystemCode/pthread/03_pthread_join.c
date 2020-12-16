/*
 * 学习线程回收函数
 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

struct thrd{
  int var;
  char str[255];
};
void sys_err(const char *str)
{
  perror(str);
  exit(1);
}
void *tfn(void *arg)
{
  struct thrd *tval;
  tval=malloc(sizeof(tval));

  tval->var=100;
  strcpy(tval->str,"hello,world");

  return (void *)tval;
}
int main(int argc,char *argv[])
{
  pthread_t tid;
  struct thrd *retval;
  int ret=pthread_create(&tid,NULL,tfn,NULL);
  if(ret!=0)
  {
    sys_err("pthread_create error");
  }
  //阻塞回收子线程
  ret=pthread_join(tid,(void **)&retval);
  if(ret!=0)
  {
    sys_err("pthread_join error");
  }
  printf("child thread exit with var=%d,str=%s\n",retval->var,retval->str);
  pthread_exit(NULL);
}

