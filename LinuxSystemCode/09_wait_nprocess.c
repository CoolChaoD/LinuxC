#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int i;
  pid_t pid,wpid;
  for(i=0;i<5;i++){
    pid=fork();
    if(pid==0){
        break; //循环期间子进程不fork,仅仅由一个父进程去创建5个子进程
    }
  }
  if(i==5){ //如果i=5时候说明现在已经是父进程了
   /*
      while(wpid=waitpid(-1,null,0)){
      printf("wait child %d \n",wpid);
    }
    */

      while((wpid=waitpid(-1,NULL,WNOHANG))!=-1){
         if(wpid>0){
               printf("wait child %d \n",wpid);
          }else if(wpid==0){
            sleep(1);
            continue;
            
          }
      }
  }else{ //子进程从break跳出后到这里来了
    sleep(i);
    printf("i am the %dth child,pid=%d\n",i+1,getpid());
  }
  return 0;
}






