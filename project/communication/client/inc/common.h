#ifndef _COMMON_H_
#define _COMMON_H_

//�ͻ���
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

//����һ���ṹ��������ſͻ��˵ĵ�ַ�ṹ
typedef struct IPAddr{
	    char IP[20];
	    int port;    
}IPAddr;

//���巢�����ݵ����ݸ�ʽ
typedef struct Message{
	  struct IPAddr ipaddr;
	  char buf[1024];
}Message;



//�����Ķ���
// 01�����׽���
int Socket(int domain,int type,int protocol); 
//���׽�������  
int  Bind(int socketfd,const struct sockaddr *addr,socklen_t addrlen);
//���ü�������
int Listen(int socketfd,int backlog);
//�����ȴ�
int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
//�ͻ������ӷ�����
int Connect(int fd,const struct sockaddr *sa, socklen_t salen);
int Close(int fd);

#endif

