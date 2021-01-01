#ifndef _COMMON_H_
#define _COMMON_H_

//客户端
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <arpa/inet.h>
#include <strings.h>

//定义一个结构体用来存放客户端的地址结构
typedef struct IPAddr{
	    char IP[20];
	    int port;    
}IPAddr;

//定义发送数据的数据格式
typedef struct Message{
	  struct IPAddr ipaddr;
	  char buf[1024];
}Message;



//函数的定义
// 01创建套接字
int Socket(int domain,int type,int protocol); 
//给套接字命名  
int  Bind(int socketfd,const struct sockaddr *addr,socklen_t addrlen);
//设置监听上限
int Listen(int socketfd,int backlog);
//阻塞等待
int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
//客户端连接服务器
int Connect(int fd,const struct sockaddr *sa, socklen_t salen);
int Close(int fd);

#endif

