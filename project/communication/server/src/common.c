#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include "common.h"

void perr_exit(const char* str)
{
	perror(str);
	exit(1);
}


//封装socket
int Socket(int domain,int type,int protocol)
{
  int n;
  if((n=socket(domain,type,protocol))<0)
  	perr_exit("socket error");
  	return n;
}

//封装bind
int  Bind(int socketfd,const struct sockaddr *addr,socklen_t addrlen)
{
	int n;
	if((n=bind(socketfd,addr,addrlen))<0)
		perr_exit("bind error");
	return n;
}

//封装listen
int Listen(int sockfd,int backlog)
{
	int n;
	if((n=listen(sockfd,backlog))<0)
		perr_exit("listen error");
	return n;
}

//封装accept
int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen)
{
	int n;
again:
		if((n=accept(sockfd,addr,addrlen))<0){
			if((errno==ECONNABORTED)||(errno==EINTR))
				goto again;
			else{ 
				perr_exit("accept error");
			 }
		}
	return n;
}

//封装Connect
int Connect(int fd,const struct sockaddr *sa, socklen_t salen)
{
	int n;
	if((n=connect(fd,sa,salen))<0)
		perr_exit("connect error");
} 

int Close(int fd)
{
	int n;
	if((n=close(fd))<0)
		perr_exit("close error");
	return n;
}

