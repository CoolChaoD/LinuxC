#include "common.h"

//定义服务器的IP地址
#define SERV_IP "127.0.0.1" 
#define SERV_PORT 6666



int main(void)
{
	//变量声明
	pid_t pid; //客户端需要有两个进程一个用来读取一个用来发送
	int nfd,len;
	struct sockaddr_in serv_addr;
	char buf[4096];
	Message message;     //声明一个发送数据的结构体
	
	
	
	//创建一个socket 指定IPV4 采用TCP来进行连接
	nfd=socket(AF_INET,SOCK_STREAM,0);
	
	//初始化地址结构
	bzero(&serv_addr,sizeof(serv_addr));  //清零
	serv_addr.sin_family=AF_INET;   //IPV4
	//将IP地址的字符串类型转换成网络字节序，参数3 是传出参数
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
	//将端口号从主机字节序转化成网络字节序
	serv_addr.sin_port=htons(SERV_PORT);
	//根据地址结构连接指定服务器
	Connect(nfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	//接收服务器的地址并写到显示屏幕上
	struct IPAddr clientRecv;
	char cli_IP[1024];
	len=read(nfd,buf,sizeof(buf));
	memcpy(&clientRecv,buf,len);
	//printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&clientRecv.IP,cli_IP,sizeof(cli_IP)),ntohs(clientRecv.port));
	printf("MyIP:%s:Port:%d\n",clientRecv.IP,clientRecv.port);
	pid=fork(); //fork创建了一个子进程
	if(pid>0)
	{
		//说明进入了父进程，父进程用来发送数据给客户端
		while(1)
		{
			printf("Please input the destination IP:Port and send message \n");
	    scanf("%s\n",message.ipaddr.IP);     
			char n[10];	
			fgets(n,sizeof(n),stdin);
			sscanf(n,"%d",&message.ipaddr.port); //将字符串转换成整数					
	    //从标准输入中获取数据
			fgets(message.buf,sizeof(message.buf),stdin);    
		  printf("%s:%d,data:%s",message.ipaddr.IP,message.ipaddr.port,message.buf);
			memcpy(buf,&message,sizeof(Message));
			//将数据写给服务器
			write(nfd,buf,sizeof(buf));
	  }
	}else if(pid==0){
		//进入子进程
		while(1)
		{
			//循环监听服务器发送过来的消息
			
			len=read(nfd,buf,sizeof(buf));
			write(STDOUT_FILENO,buf,len);//将从服务器上接收到的信息输出到你显示屏上
		}
	}else{
		perror("fork error");
		exit(1);
	}
	//关闭连接
	Close(nfd);
	return  0;
}