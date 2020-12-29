#include "common.h"

//定义服务器的IP地址
#define SERV_IP "47.96.255.54" 
#define SERV_PORT 6666

int main(void)
{
	int nfd,len;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];
	
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
	connect(nfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	while(1){
		//从标准输入中获取数据
		fgets(buf,sizeof(buf),stdin);
		//将数据写给服务器
		write(nfd,buf,strlen(buf));
		//从服务器读取数据返回给服务器
		len=read(nfd,buf,sizeof(buf));
		//写到标准输出
		write(STDOUT_FILENO,buf,len);
	}
	
	//关闭连接
	close(nfd);
	return  0;
}