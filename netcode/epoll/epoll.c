#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include <sys/socket.h>
#include "wrap.h"



#define MAXLINE 8192
#define SERV_PORT 6666 

#define OPEN_MAX 5000

int main(int argc,char* argv[])
{
  int i,listenfd,connfd,sockfd;
  int n,num=0;
  ssize_t nready,efd,res;
  char buf[MAXLINE],str[INET_ADDRSTRLEN];
  socklen_t clien;  //定义客户端的地址结构的长度

  struct sockaddr_in cliaddr,servaddr; //定义客户端与服务器的地址结构

  listenfd=Socket(AF_INET,SOCK_STREAM,0); //创建监听套接字
  int opt=1;
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //将主机字节序转化为网络字节序
  servaddr.sin_port=htons(SERV_PORT); //将端口号转化为网络字节序
  Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); //给监听套接字绑定地址结构
  Listen(listenfd,20); //设置监听上限

  efd=epoll_create(OPEN_MAX); //创建epoll模型，efd，指向红黑树的根节点
  if(efd==-1)
  {
    perr_exit("epoll_create error");
  }

  struct epoll_event tep, ep[OPEN_MAX]; //tep:epoll_ctl参数，ep[]:epoll_wait参数

  tep.events=EPOLLIN;
  tep.data.fd=listenfd;  //指定lfd的监听为读

  res=epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep); //将lfd以及对应的结构体设置到树上，efd可以找到该树
  if(res==-1)
  {
    perr_exit("epoll_ctl error");
  }

  for(;;){
    //epoll为server监听阻塞事件，ep为 epoll_event类型数组，OPEN_MAX为数组容量，-1代表永久阻塞
    nready=epoll_wait(efd,ep,OPEN_MAX,-1);
    if(nready==-1)
    {
      perr_exit("epoll wait error");
    }

    for(i=0;i<nready;i++)
    {
      if(!(ep[i].events & EPOLLIN)) //如果不是读事件，则继续循环
        continue;
      if(ep[i].data.fd==listenfd) //判断满足条件的事件是不是lfd
      {
        clien=sizeof(cliaddr);
        connfd=Accept(listenfd,(struct sockaddr *)&cliaddr,&clien); //接收连接
        printf("received form %s:%d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
        printf("cfd %d--client %d\n",connfd,++num);
        tep.events=EPOLLIN;
        tep.data.fd=connfd;
        res=epoll_ctl(efd,EPOLL_CTL_ADD,connfd,&tep);//将新创建的监听套接字加入到红黑树中
        if(res==-1)
        {
          perr_exit("epoll_ctl error");
        }
      }else{ //如果不是监听套接字，那么就是通信套接字
        sockfd=ep[i].data.fd;
        n=read(sockfd,buf,MAXLINE);
        if(n==0) //读到0说明客户端关闭连接
        {
          res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);//对端关闭连接，将该文件描述符从红黑树中取出
          if(res==-1)
          {
            perr_exit("epoll_ctl error");
          }
          close(sockfd);
          printf("client[%d] closed connection\n",sockfd);
        }else if(n<0) //出错
        {
          perror("read n<0 error: ");
          res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);//对端关闭连接，将该文件描述符从红黑树中取出
          close(sockfd);
        }else{
          for(i=0;i<n;i++)
          {
            buf[i]=toupper(buf[i]); //小写转大写返回给客户端
          }
          write(sockfd,buf,n);
          write(STDOUT_FILENO,buf,n); 
        }
      }
    }
  }
  close(listenfd);
  close(efd);
  return 0;
}

















