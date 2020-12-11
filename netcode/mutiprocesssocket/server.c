/*
 * 利用多进程编写高并发服务器
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <strings.h>
#include <arpa/inet.h>

#include "wrap.h"


#define SERV_PORT 9527 //定义服务器的端口
void catch_waitpid(int signo)
{
  //信号捕捉函数
  while((waitpid(0,NULL,WNOHANG))>0);
  return ;
}
int main()
{
  int lfd,cfd;
  pid_t pid;
  struct sockaddr_in srv_addr,clt_addr; //定义服务器和客户端的地址结构体
  socklen_t clt_addr_len;
  char buf[BUFSIZ];
  int ret,i;

  bzero(&srv_addr,sizeof(srv_addr)); //将地址结构体清零

  srv_addr.sin_family=AF_INET; //网络协议，选择IPV4
  srv_addr.sin_port=SERV_PORT; //服务器的进程号
  srv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //服务器的IP地址,主机字节转化成网络字节序

  lfd=Socket(AF_INET,SOCK_STREAM,0);  //创建监听套接字
  Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));  //将Ip地址绑定到lfd上
  Listen(lfd,128); //设置同时监听的数量
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
    }else{
      //父进程
      //在父进程中注册回收函数，但是这个时候也要注意一个问题，那就是在注册函数正在执行的时候有子进程死亡这时候就没法回收子进程了
      //因此在注册函数调用好之前我们将sigchild信号屏蔽掉

      //阻塞屏蔽SIGCHLD
      sigset_t set,oldset; //创建自定义信号集
      sigaddset(&set,SIGCHLD); //将SIGCHLD信号加入到我们的信号集中
      ret=sigprocmask(SIG_BLOCK,&set,&oldset);

      struct sigaction act;
      act.sa_flags=0;
      act.sa_handler=catch_waitpid;
      sigemptyset(&act.sa_mask);//清空信号屏蔽字
      ret=sigaction(SIGCHLD,&act,NULL); //参数三，传NULL代表不需要知道之前是怎样执行的
      if(ret==-1)
      {
        perr_exit("sigaction error");
      }
      sigprocmask(SIG_UNBLOCK,&set,&oldset);
      close(cfd);//父进程关闭连接套接字
      continue;
    }
  }
  if(pid==0)
  {
    //子进程内要完成cfd中读取数据并转化成大写，然后写到屏幕上
    for(;;){
    ret=read(cfd,buf,sizeof(buf));
    if(ret==0)
    {
      close(cfd);
      exit(1);
    }
    for(i=0;i<ret;i++)  
    {
      buf[i]=toupper(buf[i]);
    }
    write(cfd,buf,ret);
    write(STDOUT_FILENO,buf,ret); //写到屏幕上
    }
  }
  return 0;
}

