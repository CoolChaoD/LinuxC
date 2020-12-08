#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 9527

void sys_err(const char*str)
{
  perror(str);
  exit(1);
}



int main()
{

  int cfd;
  int conter=10;
  char buf[BUFSIZ];

  struct sockaddr_in serv_addr; //服务器的地址结构
  
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(SERV_PORT);
  int ret=inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr); //将点分十进制的IP地址转化成网络字节序的地址
  if(ret==-1)
  {
    sys_err("inet_pton error");
  }

  cfd=socket(AF_INET,SOCK_STREAM,0);
  if(cfd==-1)
  {
    sys_err("socket error");
  }

  ret=connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  if(ret==-1)
  {
    sys_err("connect error");
  }

  while(conter--)
  {
    sleep(1);
    ret=write(cfd,"hello\n",6);
    if(ret==-1)
    {
      sys_err("write error");
    }
    ret=read(cfd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,ret); //写到屏幕上


  }
  close(cfd);
  return 0;
  
}



