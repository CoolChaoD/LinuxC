
#include  <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(){

  //创建一个子进程
  pid_t pid=fork();
  if(pid==-1){
    printf("子进程创建失败\n");
  }else if(pid==0){
    printf("子进程创建成功,子进程的PID是%d\n",getpid());

  }else if(pid>0){
    printf("我是父进程，子进程的PID是%d\n",pid);
  }


  return 0;
}












