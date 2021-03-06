#include "common.h"

//定义服务器的端口号
#define SERV_PORT 6666



void waitchild(int signo)
{
	while((waitpid(0,NULL,WNOHANG)>0));
	return;
}

int main()
{
	//声明监听套接字和连接套接字
	int lfd,cfd,ret;
	pid_t pid;
	char buf[4096];
	int i;
	//用于存储客户端的IP地址
	char cli_IP[1024];
  Message recvMessage;
  struct IPAddr clientAddr;
  
  
  
  //创建共享内存映射
  Message *p;
  int fd;
  //打开一个文件
  fd=open("./mmap.txt",O_RDWR|O_CREAT);
  if(fd<0)
  	{
  		perror("open error");
  	}
   ftruncate(fd,sizeof(recvMessage));
   p=mmap(NULL,sizeof(recvMessage),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    perror("mmap error");
    exit(1);
  }
  Close(fd); //共享内存映射区创建完毕后可以关闭文件描述符

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

  //获取客户端的地址结构大小
  cli_addr_len=sizeof(cli_addr);

  struct IPAddr clientAddrList[1024];  //存放已经连接的客户端的地址结构
  printf("Accepting connections...\n");
  int m=0;
  while(1)
  {
    //最多连接1024个服务器
   if(m<1024)
   {	
   //04_阻塞等待客户端的连接，参数1:监听套接字lfd,参数2:传入参数，参数3：传出参数
   cfd=Accept(lfd,(struct sockaddr*)&cli_addr,&cli_addr_len);
  // printf("-------------------%d\n",cfd);
   printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,cli_IP,sizeof(cli_IP)),ntohs(cli_addr.sin_port));
   
   //将客户端的地址结构存放到结构体内部
   
   strncpy(clientAddr.IP,cli_IP,strlen(cli_IP));
   clientAddr.port=ntohs(cli_addr.sin_port);   
   
   memset(buf,0,1024); //将buf清零
	 memcpy(buf,&clientAddr,sizeof(IPAddr));
	 //printf("child %s:%d\n",clientAddr.IP,clientAddr.port);
	 write(cfd,buf,sizeof(buf)); //将客户端的地址结构发送给客户端	 
  // printf("%s:%d",clientAddr.IP,clientAddr.port);
   //将结构体中的元素添加到数组当中  
   clientAddrList[m]=clientAddr;
   //printf("%s:%d",clientAddrList[0].IP,clientAddrList[0].port);
   //赋值完毕后清空结构体
   bzero(&clientAddr,0);
    m++;
   }else{
   	printf("客户端连接数量超过上限\n");
   	break;
   }
    
   pid=fork();
   if(pid==0){
   	//进入子进程
   	Close(lfd); //子进程无须监听，关闭监听套接字
   	break;
   }else if(pid>0){
   	//进入父进程
   	//父进程首先要做的就是注册捕捉函数回收子进程
   	struct sigaction act;
   	act.sa_flags=0;
   	act.sa_handler=waitchild;
   	//父进程首先清空阻塞信号集
   	sigemptyset(&act.sa_mask);
   	ret=sigaction(SIGCHLD,&act,NULL);
    Close(cfd); //父进程无须通信因此关闭与客户端的通信的套接字
   	continue;
   }else{
		perror("fork error");
   	exit(1);
   } 
  } 
  
  if(pid==0)
   {  	
   	 int len;
   	 IPAddr myAddr;
   	 IPAddr recvAddr;
   	 myAddr=clientAddr; //每一个子进程中都有一个地址结构存储着自己的地址结构  	 
   	 printf("my pid is %d\n",getpid());	 	
   	 printf("======================\n");
   	 while(1){    	
   	 	  for(int j=0;j<3;j++)
   	 	 {        	 	  
   	 	  recvAddr=p->ipaddr;	 	 	 
   	 	  printf("I am a child process for %s:%d\n",myAddr.IP,myAddr.port);	
   	 	  printf("recvAddr%s:%d\n",recvAddr.IP,recvAddr.port);
		    if(recvAddr.IP==myAddr.IP&&recvAddr.port==myAddr.port)
		    {
		    	  printf("match correct");
		    }
		   } 	
		    for(int i=0;i<3;i++)
		   {        
		   	len=read(cfd,buf,sizeof(buf)); //读取子进程发送的内容
		   	if(len==0){
		   	    //说明已经读到文件末尾了
		   	    printf("对端关闭连接");
		   	    exit(1);
		   }
		  }
        //memcpy(&recvMessage,buf,len);
        //printf("from client:\n");
        //printf("%s:%d,data:%s\n",recvMessage.ipaddr.IP,recvMessage.ipaddr.port,recvMessage.buf);
		    memcpy(p,buf,len);       
        //printf("recvAddr%s:%d\n",recvAddr.IP,recvAddr.port);
		    //printf("%s:%d,data:%s\n:",p->ipaddr.IP,p->ipaddr.port,p->buf);
		  
     }   
   }
  return 0;
}

