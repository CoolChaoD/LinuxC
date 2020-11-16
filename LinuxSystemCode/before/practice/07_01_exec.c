#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


int main(){
  //创建一个子进程
  pid_t pid=fork();
  if(pid==-1){
    perror("fork error");
    exit(1);
  }else if(pid==0){
    printf("进入子进程，开始执行execlp\n");
    execlp("date","date",NULL);
    //如果没有执行成功的话，那么就打印错误
    perror("exec error!");
    exit(1);
  }else if(pid>0){
    sleep(1);
    printf("我是父进程，我的pid是%d\n",getppid());
  }
  return 0;
}
