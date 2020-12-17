#ifndef _WRAP_H_
#define _WRAP_H_
#include <sys/socket.h>
#include <unistd.h>

//创建套接字
int Socket(int domain,int type,int protocol);
void perr_exit(const char *str);
int Bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);
int Listen(int sockfd,int backlog);
int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);
int Connect(int fd, const struct sockaddr *sa, socklen_t salen);
int Close(int fd);
#endif
