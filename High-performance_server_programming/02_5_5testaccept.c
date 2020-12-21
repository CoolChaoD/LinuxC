/*
 * 本函数用来测试如果一个客户端正在连接服务器突然断开会怎么样
 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wrap.h"


#define SERV_PORT 6666 //定义服务器的端口号

void sys_err(const char* str)
{
  perror(str);
  exit(1);
}

int main() 
{
  struct sockaddr_in serv_addr,cli_addr; //定义客户端与服务器的地址结构
  int listenfd,connfd; //创建监听套接字和连接套接字
  socklen_t cli_addr_len;//客户端地址结构的大小
  bzero(&serv_addr,sizeof(serv_addr));

  //定义服务器的地址结构
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(SERV_PORT); //定义服务器的端口号，并将主机字节序转化成网络字节序
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //取任意一个有效的IP地址作为服务器的IP地址

  //1.创建监听套接字
  listenfd=Socket(AF_INET,SOCK_STREAM,0);
  //2.给socket命名
  Bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
  //3.设置监听上限
  Listen(listenfd,5);
  //暂停20s
  sleep(20);
  cli_addr_len=sizeof(cli_addr); //这是一个传入传出参数，传入客户端的地址大小，传出连接客户端的实际大小
  connfd=Accept(listenfd,(struct sockaddr *)&cli_addr,&cli_addr_len);
  //打印连接的客户端的IP地址和端口号
  char str[INET_ADDRSTRLEN];
  printf("connected with ip:%s and port: %d\n",inet_ntop(AF_INET,&cli_addr.sin_addr,str,sizeof(str)),ntohs(cli_addr.sin_port));

  close(connfd);  //关闭连接套接字
  close(listenfd); //关闭通信套接字
  return 0;
}

