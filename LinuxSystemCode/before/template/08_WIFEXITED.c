#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t pid,wpid;
  int status;
  pid=fork();
  if(pid==0){
    printf("--------子进程创建成功，ID=%d\n",getpid());
    sleep(102);
    printf("--------child process die------------\n");
    return 73;
  }else if(pid>0){
    wpid=wait(&status);//如果子进程未终止，那么父进程会一直阻塞在这个函数上
    if(wpid==-1){
      perror("wait error");
      exit(1);
    }
    if(WIFEXITED(status)){ //如果为真说明子进程正常终止
      printf("child exit with %d\n",WEXITSTATUS(status));
    }
    if(WIFSIGNALED(status)){  //为真，说明子进程是被信号终止
      printf("child killed with signal %d\n",WTERMSIG(status));

    }
    printf("-------------parent wait finish:%d\n",wpid);
  }else{
    perror("fork error");
    return 1;
  }
}
