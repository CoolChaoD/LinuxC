/*
 * 增强版的select增加了一个数组
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "wrap.h"

#define SERV_PORT 6666 

int main()
{
  int i,j,n,maxi;

  int nready,client[FD_SETSIZE]; //自定义数组client,防止遍历1024个文件描述符， FD_SETSIZE默认为1024
  int maxfd,listenfd,connfd,sockfd;
  char buf[BUFSIZ],str[INET_ADDRSTRLEN];

  struct sockaddr_in cli_addr,serv_addr;
  socklen_t clie_addr_len;

  fd_set rset,allset; //reset读事件文件描述符集合， allset用来暂存

  listenfd=Socket(AF_INET,SOCK_STREAM,0);

  //设置端口复用
  int opt=1;
  setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=htons(SERV_PORT); 

  Bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)); //绑定地址结构
  Listen(listenfd,128); //设置监听上限

  maxfd=listenfd;    //起初 listenfd 即为最大文件描述符

  maxi=-1; //将用用作client[]的下标，初始值指向0个元素之前下标位置
  for(i=0;i<FD_SETSIZE;i++)
  {
    client[i]=-1; //用-1来统一初始化client[]
  }

  FD_ZERO(&allset); //构造select监控文件描述符集
  FD_SET(listenfd,&allset); //将listenfd添加进去

  while(1)
  {
    rset=allset; //每次循环都重新设置select监控信号集
    nready=select(maxfd+1,&rset,NULL,NULL,NULL); //返回实际发生的事件个数
    if(nready<0)
    {
      perr_exit("select error");
    }
    if(FD_ISSET(listenfd,&rset)) //说明有新的客户端连接请求,处理新的连接请求
    {
      clie_addr_len=sizeof(cli_addr);
      connfd=Accept(listenfd,(struct sockaddr *)&cli_addr,&clie_addr_len); //Accept不会阻塞
      printf("Received from %s:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr,str,sizeof(str)),ntohs(cli_addr.sin_port)); //将数值型的IP地址转化成淀粉十进制

      for(i=0;i<FD_SETSIZE;i++)
      {
        if(client[i]<0){      //找client[]中没有使用的位置
          client[i]=connfd; //保存accept返回的文件描述符
          break;
        }
      }
      FD_SET(connfd,&allset); //向监控文件描述符集合中添加新的文件描述符connfd

      if(connfd>maxfd)
      {
        maxfd=connfd;       //select第一个参数需要
      }
      if(i>maxi){
        maxi=i;       //保证maxi始终是client[]最后一个文件元素的下标
      }
      if(--nready==0)
      {
        continue;
      }
    }

    for(i=0;i<=maxi;i++)
    {
      if((sockfd=client[i])<0)
        continue;
      if(FD_ISSET(sockfd,&rset))
      {
        if((n=read(sockfd,buf,sizeof(buf)))==0) //当client关闭连接的时候，服务器端也关闭对应链接
        {
          close(sockfd);
          FD_CLR(sockfd,&allset); //解除select对此文件描述符的监控
          client[i]=-1;
        }
        else if(n>0)
        {
          for(j=0;j<n;j++)
          {
            buf[j]=toupper(buf[j]);
          }
          write(sockfd,buf,n);
          write(STDOUT_FILENO,buf,n);
        }
        if(--nready==0)
          break;          //跳出for循环，但是还是在while循环中
      }
    }
  }
  close(listenfd);
  return 0;
}
