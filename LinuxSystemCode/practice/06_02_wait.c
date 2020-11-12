/*
 * 练习使用wait函数
 * wait函数用来回收进程主要有三大作用
 * 1.阻塞等待子进程的退出
 * 2.回收子进程残留饿资源
 * 3.异常终止导致该进程终止的信号是哪个
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
  pid_t pid,wpid;
  pid=fork();
  int status;

  if(pid==0){
    printf("----I am the child process,I am going to sleep 10s-------------\n");
    sleep(10);
    printf("-----------child process die----------------------\n");
  }else if(pid>0){
    printf("-------------I am the parent process,I am wait my child process\n------------");
    wpid=wait(&status); //wait函数成功返回回收子进程的ID，失败返回-1
    if(wpid==-1){
      perror("wait error");
      exit(1);
    }
    printf("----------parent wait the child process%d,and recycle %d\n-----------",pid,wpid);
  }else{

    perror("fork error");
    exit(1);
  }
  return 0;
}
