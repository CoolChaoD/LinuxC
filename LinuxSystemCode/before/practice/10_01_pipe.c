/*
  练习父子进程之间的通信
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


int main(){
 

  char const *str="hello pipe\n";

  int fd[2]; //存放文纪念描述符
  char buf[1024];
  int ret;
  int retsize;
  pid_t pid;

  ret=pipe(fd);//创建一个管道
  if(ret==-1){
    //如果返回值是-1代表创建失败
    perror("pipe error\n");
    exit(1);
  }
  pid=fork();
  if(pid<0){
    perror("fork error");
    exit(1);
  }
  //进入子进程
  //编写代码，从子进程写入，父进程读出，并打印的屏幕上
  if(pid==0){
     close(fd[0]);
     write(fd[1],str,strlen(str));
     close(fd[1]); 
  }else if(pid>0){
    //进入父进程，父进程读
    close(fd[1]); //父进程关闭写
    retsize=read(fd[0],buf,sizeof(buf));
    printf("接收了%d个字节\n",retsize);
    write(STDOUT_FILENO,buf,retsize);
    close(fd[0]);

  }

  return 0;
}
