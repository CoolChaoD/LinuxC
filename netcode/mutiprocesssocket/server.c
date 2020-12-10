/*
 * 利用多进程编写高并发服务器
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include "wrap.h"


#define SERV_PORT=9999 //定义服务器的端口9999

int main()
{
  int lfd,int cfd;

  pid_t =pid;
  struct sockaddr_in srv_addr,clt_addr; //定义服务器和客户端的地址结构体
  socklen_t clt_addr_len;
  char buf[BUFSIZ];
  int ret,i;

  bzero(&srv_sock,sizeof(srv_addr)); //将地址结构体清零

  srv_addr.sin_family=AF_INET; //网络协议，选择IPV4
  srv_addr.sin_port=SERV_PORT; //服务器的进程号
  srv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //服务器的IP地址,主机字节转化成网络字节序

  lfd=Socket(AF_INET,SOCK_STREAM,0);
  Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));  //将Ip地址绑定到lfd上
  Listen(lfd,128); //设置同时监听的数量




  

}

