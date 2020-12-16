#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;//创建一把锁
  
void *tfn(void *arg)
{
  srand(time(NULL)); //用当前时间来设置随机数种子
  while(1)
  {
    pthread_mutex_lock(&mutex); //加锁
    printf("hello ");
    sleep(rand()%3); //模拟长时间操作资源，导致cpu易主
    printf("world\n");
    pthread_mutex_unlock(&mutex); //解锁
    sleep(rand()%3);
  }
}

int main()
{
  pthread_t tid; //子线程号
  srand(time(NULL));
  int ret=pthread_mutex_init(&mutex,NULL);  //初始化锁
  pthread_create(&tid,NULL,tfn,NULL);  //创建一个子线程
  while(1)
  {
    
    pthread_mutex_lock(&mutex); //加锁
    printf("HELLO ");
    sleep(rand()%3);
    printf("WORLD\n");
    pthread_mutex_unlock(&mutex); //解锁
    sleep(rand()%3);
  }
  pthread_join(tid,NULL); //回收子线程
  ret=pthread_mutex_destroy(&mutex);  //销毁锁

  return 0;
}
  


