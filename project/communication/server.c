#include "common.h"

//定义服务器的端口号
#define SERV_PORT 6666

int main()
{
	//声明监听套接字和连接套接字
	int lfd,cfd; 
	
	char buf[BUFSIZ];
	
	//用于存储客户端的IP地址
	char cli_IP[1024];
	
	//定义客户端与服务器的地址结构
	struct sockaddr_in serv_addr,cli_addr;
	//客户端的地址结构长度
	socklen_t cli_addr_len;
	
	//01_创建一个监听socket,采用AF_INET(IPV4),SOCK_STREAM(TCP协议)
	lfd=Socket(AF_INET,SOCK_STREAM,0); 
	
	int opt=1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	//初始化服务器的地址结构
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //将主机字节序转换成网络字节序
	serv_addr.sin_port=htons(SERV_PORT); //将主机字节序转换成网络字节序
	
	
	//02_绑定服务器的地址结构、
  Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
  
  //03_设置监听上限,此处是非阻塞的
  Listen(lfd,64);
  
  printf("wait for client connect.....\n");

  
  //获取客户端的地址结构大小
  cli_addr_len=sizeof(cli_addr);
  
  //04_阻塞等待客户端的连接，参数1:监听套接字lfd,参数2:传入参数，参数3：传出参数 
  cfd=Accept(lfd,(struct sockaddr*)&cli_addr,&cli_addr_len);

  printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,cli_IP,sizeof(cli_IP)),ntohs(cli_addr.sin_port));
  
  while(1)
  {
  	//读取客户端发送的数据
  	int len=read(cfd,buf,sizeof(buf)); //返回读取到的字节数
  	write(STDOUT_FILENO,buf,len);      //将读入的数据写到屏幕上
  	
  	//给客户端一个回应
  	
    const char str[1024]= {"copy that"};
  	write(cfd,str,sizeof(str));
  }
  
  //关闭套接字
  Close(lfd);
  Close(cfd);
  
  return 0;	
}

