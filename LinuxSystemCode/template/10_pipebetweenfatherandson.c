/*
 *创建管道实现父子进程之间的通信
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>



void sys_err(const char* str){
  perror(str);
  exit(1);
}

int main(){
  int ret;  //pipe的返回值，创建成功返回0，失败返回-1
  int fd[2]; //文件描述符
  pid_t pid; 

  char const  *str="hello pipe\n";
  char buf[1024];//定义一个可以存放1024个字节的数组

  ret=pipe(fd);//管道创建后会获得一对文件描述符，fd[0]指向读端，fd[1]指向写端
  if(ret==-1){
    sys_err("pipe error");
  }

  pid=fork(); //fork创建子进程，0表示创建成功
  if(pid>0){    //pid>0父进程
    close(fd[0]); //父进程关闭读
    write(fd[1],str,strlen(str)); //str将要发送的数据，第三个参数表示将要发送数据的大小，write函数将从buf中写入数据到fd[1]
    close(fd[1]);
  }else if(pid==0){ //子进程
    close(fd[1]); //子进程关闭写端
    ret=read(fd[0],buf,sizeof(buf)); //ret表示返回消息的长度,read函数表示将fd中的文件读取count个字节进入buf中
    write(STDOUT_FILENO,buf,ret);//将读取到的数据写入到屏幕上
    close(fd[0]); //关闭读端
  }
  return 0;
}
