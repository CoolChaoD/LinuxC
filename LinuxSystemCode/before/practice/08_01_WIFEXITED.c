#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  pid_t pid,wpid;
  int status;
  pid=fork();
  if(pid==0){
    printf("子进程创建成功，PID=%d\n",getpid());
    sleep(102);
    printf("子进程死亡\n");
    return 1111;
  }else if(pid>0){
    wpid=wait(&status); //如果子进程未终止，那么父进程就会一直阻塞在这个函数上
    if(wpid==-1){
      perror("wait error");
      exit(1);
    }
    if(WIFEXITED(status)!=0){ //如果这个不等于0 说明是正常结束
      printf("child exit with %d\n",WEXITSTATUS(status));
    }
    if(WIFSIGNALED(status)!=0){ //如果WIFSIGNALED为真说明子进程被信号终止
      printf("child killed with signal %d\n",WTERMSIG(status));

    }
    printf("父进程等待结束");

  }else{
    perror("fork eror");
    exit(1);
  }
  return 0;
}

