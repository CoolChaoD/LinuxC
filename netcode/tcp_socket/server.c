#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 9527

void sys_err(const char*str)
{
  perror(str);
  exit(1);
}
int main()
{
  int lfd=0;
  int cfd=0;
  int ret;
  char buf[BUFSIZ];
  struct sockaddr_in serv_addr,clit_addr;
  socklen_t clit_addr_len; //传入传出参数

  //地址结构
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //将主机字节序转化成网络字节序
  serv_addr.sin_port=htons(SERV_PORT);

  lfd=socket(AF_INET,SOCK_STREAM,0);
  if(lfd==-1)
  {
    sys_err("socket error");
  }

  //绑定一个地址结构到socket上
  ret=bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  if(ret==-1)
  {
    sys_err("bind error");
  }

  //设置监听数
  ret=listen(lfd,128);
  if(ret==-1)
  {
    sys_err("listen error");
  }

  //阻塞等待客户端建立连接并返回一个与客户端成功建立连接的socket文件描述符
  clit_addr_len=sizeof(clit_addr);
  cfd=accept(lfd,(struct sockaddr*)&clit_addr,&clit_addr_len);
  if(cfd==-1)
  {
    sys_err("accept error");
  }

  while(1)
  {
    ret=read(cfd,buf,sizeof(buf));
    if(ret==-1)
    {
      sys_err("read error");
    }
    int ret_w=write(STDOUT_FILENO,buf,ret);
    if(ret_w==-1)
    {
      sys_err("write error");
    }

    for(int i=0;i<ret;i++)
    {
      buf[i]=toupper(buf[i]);
    }
    write(cfd,buf,ret);

  }

  close(lfd);
  close(cfd);
  return 0;
}
