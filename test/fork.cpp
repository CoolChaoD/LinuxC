#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main(){

        pid_t pid;
        pid=fork();//当fork成功调用后，子进程开始从fork后开始执行
        
        //创建进程失败
        if(pid==-1){
          perror("fork failed");
          return -1;

        }
        //父进程
        else if(pid>0){

        //pid用于接收当前进程id,ppid用于接收父进程id
                printf("parent:pid=%d,ppid=%d\n",getpid(),getppid());
                sleep(1);
        }
        else if(pid==0){

           printf("child:pid=%d,ppid=%d",getpid(),getppid());
                printf("\n");
                sleep(1);
        }
       return 0;
}
