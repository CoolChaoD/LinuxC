#include "common.h"

//����������Ķ˿ں�
#define SERV_PORT 6666

int main()
{
	//���������׽��ֺ������׽���
	int lfd,cfd; 
	
	char buf[BUFSIZ];
	
	//���ڴ洢�ͻ��˵�IP��ַ
	char cli_IP[1024];
	
	//����ͻ�����������ĵ�ַ�ṹ
	struct sockaddr_in serv_addr,cli_addr;
	//�ͻ��˵ĵ�ַ�ṹ����
	socklen_t cli_addr_len;
	
	//01_����һ������socket,����AF_INET(IPV4),SOCK_STREAM(TCPЭ��)
	lfd=Socket(AF_INET,SOCK_STREAM,0); 
	
	int opt=1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	//��ʼ���������ĵ�ַ�ṹ
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //�������ֽ���ת���������ֽ���
	serv_addr.sin_port=htons(SERV_PORT); //�������ֽ���ת���������ֽ���
	
	
	//02_�󶨷������ĵ�ַ�ṹ��
  Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
  
  //03_���ü�������,�˴��Ƿ�������
  Listen(lfd,64);
  
  printf("wait for client connect.....\n");

  
  //��ȡ�ͻ��˵ĵ�ַ�ṹ��С
  cli_addr_len=sizeof(cli_addr);
  
  //04_�����ȴ��ͻ��˵����ӣ�����1:�����׽���lfd,����2:�������������3���������� 
  cfd=Accept(lfd,(struct sockaddr*)&cli_addr,&cli_addr_len);

  printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,cli_IP,sizeof(cli_IP)),ntohs(cli_addr.sin_port));
  
  while(1)
  {
  	//��ȡ�ͻ��˷��͵�����
  	int len=read(cfd,buf,sizeof(buf)); //���ض�ȡ�����ֽ���
  	write(STDOUT_FILENO,buf,len);      //�����������д����Ļ��
  	
  	//���ͻ���һ����Ӧ
  	
    const char str[1024]= {"copy that"};
  	write(cfd,str,sizeof(str));
  }
  
  //�ر��׽���
  Close(lfd);
  Close(cfd);
  
  return 0;	
}

