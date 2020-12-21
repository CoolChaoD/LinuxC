#include "wrap.h"
#include <signal.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void waitchild(int signo)
{
  while((waitpid(0,NULL,WNOHANG)>0));
    return ; 
}

int main()
{
  pid_t pid;
  struct sockaddr_in serv_addr, clt_addr;//创建服务器和客户端地址结构体
  int lfd,cfd; //创建监听和接受文件描述符
  int ret,i;

  socklen_t clt_addr_len; //客户端地址结构体的长度
  char buf[BUFSIZ]; //buf的大小

  bzero(&serv_addr,sizeof(serv_addr)); //清空服务器地址结构体

  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(9527);  //服务器的端口
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //取任意一个有效的IP地址作为服务器的IP地址

  //1.创建监听套接字
  lfd=Socket(AF_INET,SOCK_STREAM,0);

  //2.给套接字绑定地址结构
  Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

  //3.设置监听
  Listen(lfd,128);

  clt_addr_len=sizeof(clt_addr);
  while(1)
  {
    cfd=Accept(lfd,(struct sockaddr *)&clt_addr,&clt_addr_len);

    pid=fork();
    if(pid<0)
    {
      perr_exit("fork error");

    }else if(pid==0)
    {
      //进入子进程
      Close(lfd); //子进程关闭监听套接字
      break;
    }else
    {
      //父进程注册捕捉函数回收子进程
      struct sigaction act;
      act.flags=0;
      act.sa_handler=waitchild;
      sigemptyset(&act.sa_mask);
      ret=sigaction(SIGCHLD,&act,NULL);
      if(ret==-1)
      {
        perr_exit(1);
      }
      
      close(cfd);
      continue;
    }
  }

  if(pid==0)
  {
    //进入子进程
    for(;;){
      ret=read(cfd,buf,sizeof(buf));
      if(ret==0) //ret==0代表已经读取到文件的末尾了
      {
        close(cfd);
        exit(1);
      }
      for(i=0;i<ret;i++)
      {
        buf[i]=toupper(buf[i]);
      }
      write(cfd,buf,ret);//写入客户端
      write(STDOUT_FILENO,buf,ret);
    }
  }
   
return 0;
}
