/*
 * 编写服务端代码
 */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>

void sys_err(const char* str)
{
  perror(str);
  exit(1);
}
int main()
{
  int lfd,cfd;
  char buf[BUFSIZ];
  char client_IP[1024];
  //1.创建第一个socket
  lfd=socket(AF_INET,SOCK_STREAM,0);
  if(lfd==-1)
  {
    perror("socket error");
  }

  //2.绑定一个地址结构到socket当中
  struct sockaddr_in serv_addr,client_addr;//服务器的地址结构
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(9001);
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //任意有效的ip地址

  int ret=bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  if(ret==-1)
  {
    sys_err("bind error");
  }

  //3.listen设置监听的客户端数量
  ret=listen(lfd,128);
  if(ret==-1)
  {
    sys_err("listen error");
  }

  //4.阻塞等待客户端建立连接,成功的话，返回一个与客户端成功建立连接的socket文件描述符
  socklen_t client_len=sizeof(client_addr);
  cfd =accept(lfd,(struct sockaddr*)&client_addr,&client_len);
  if(cfd==-1)
  {

    sys_err("accept error");

  }
  printf("客户端的ip地址:%s:%d\n",inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_IP,sizeof(client_IP)),ntohs(client_addr.sin_port));
  //5.执行指令
  while(1)
  {  
    ret=read(cfd,buf,sizeof(buf));
    if(ret==-1)
    {
      sys_err("read error");
    }
    write(STDOUT_FILENO,buf,ret);
    for(int j=0;j<ret;j++)
    {
      buf[j]=toupper(buf[j]); //将小写字母转变成大写
    }
    write(cfd,buf,ret);
  }  
  close(lfd);
  close(cfd);
  return 0;

}



