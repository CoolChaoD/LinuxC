/*
 * 借助条件变量 模拟生产者-消费者问题
 */
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

//链表作为共享数据需要被互斥量保护

struct msg{
  struct msg *next;
  int num;
};

struct msg *head; //定义一个头结点

//静态初始化一个条件变量和一个互斥量
pthread_cond_t has_product =PTHREAD_COND_INITIALIZER; 
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
  //消费者
  struct msg *mp;
  for(;;){
    pthread_mutex_lock(&lock); //消费者加锁
    while(head==NULL){  //头指针为空，说明没有节点
      pthread_cond_wait(&has_product,&lock);//1.阻塞等待条件变量cond,2.释放已经加上去的锁，3.当被条件唤醒的时候重新加锁
    }
    mp=head;
    head=mp->next; //模拟消费了一个数据
    pthread_mutex_unlock(&lock); //解锁

    printf("Consume %lu----%d\n",pthread_self(),mp->num);
    free(mp);
    sleep(rand()%5);
  }
}


void *producer(void *p)
{

  //生产者
  struct msg *mp;
  for(;;){
    mp=malloc(sizeof(struct msg));//分配内存
    mp->num=rand()%1000+1; //模拟生产一个产品
    printf("-Produce ------------%d\n",mp->num);

    pthread_mutex_lock(&lock); //加锁
    //头插法
    mp->next=head;
    head=mp;
    pthread_mutex_unlock(&lock); //数据添加完毕后就开始解锁

    pthread_cond_signal(&has_product);//将等待在该条件变量上的一个线程唤醒
    sleep(rand()%5);
  }
}

int main()
{
  pthread_t pid,cid;
  srand(time(NULL));
  pthread_create(&pid,NULL,producer,NULL);
  pthread_create(&cid,NULL,consumer,NULL);

  pthread_join(pid,NULL);
  pthread_join(cid,NULL);

  return 0;
}



