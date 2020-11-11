#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int main(){
    pid_t pid=fork();
    if(pid==-1){
        perror("fork error");
        exit(1); //表示程序异常退出
    }else if(pid==0){
        execlp("date","date",NULL); //参数从arg1开始算
        perror("exec error");
        exit(1);
    }else if(pid>0){ //父进程

      sleep(1);
      printf("I am paernt :%d\n",getpid());
    }
   return 0;
}
