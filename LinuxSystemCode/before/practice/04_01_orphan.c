/*
 *孤儿进程：父进程提前结束，子进程变成孤儿进程被init进程回收
 *
 */
#include <stdio.h>
#include  <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
   
  pid_t pid;
  pid=fork();//创建一个子进程
  if(pid<0){
    perror("fork error");
    exit(1);
  }else if(pid==0){
    printf("I am child process,my pid is%d\n",getpid());
   sleep(1);
  }else if(pid>0){
   printf("I am parent process,my pid is %d\n",getpid());
  }
   
  return 0;
}
