#include "common.h"

//����������Ķ˿ں�
#define SERV_PORT 6666



void waitchild(int signo)
{
	while((waitpid(0,NULL,WNOHANG)>0));
	return;
}

int main()
{
	//���������׽��ֺ������׽���
	int lfd,cfd,ret;
	pid_t pid;
	char buf[1024];
	int i;
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

  //��ȡ�ͻ��˵ĵ�ַ�ṹ��С
  cli_addr_len=sizeof(cli_addr);

  struct IPAddr clientAddrList[1024];  //����Ѿ����ӵĿͻ��˵ĵ�ַ�ṹ
  printf("Accepting connections...\n");
  int m=0;
  while(1)
  {
    //�������1024��������
   if(m<1024)
   {	
   //04_�����ȴ��ͻ��˵����ӣ�����1:�����׽���lfd,����2:�������������3����������
   cfd=Accept(lfd,(struct sockaddr*)&cli_addr,&cli_addr_len);
  // printf("-------------------%d\n",cfd);
   printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,cli_IP,sizeof(cli_IP)),ntohs(cli_addr.sin_port));
   
   //���ͻ��˵ĵ�ַ�ṹ��ŵ��ṹ���ڲ�
   struct IPAddr clientAddr;
   strncpy(clientAddr.IP,cli_IP,strlen(cli_IP));
   clientAddr.port=ntohs(cli_addr.sin_port);   
   
   memset(buf,0,1024); //��buf����
	 memcpy(buf,&clientAddr,sizeof(IPAddr));
	 printf("child %s:%d\n",clientAddr.IP,clientAddr.port);
	 write(cfd,buf,sizeof(buf)); //���ͻ��˵ĵ�ַ�ṹ���͸��ͻ���	
	 
  // printf("%s:%d",clientAddr.IP,clientAddr.port);
   //���ṹ���е�Ԫ����ӵ����鵱��  
   clientAddrList[m]=clientAddr;
   //printf("%s:%d",clientAddrList[0].IP,clientAddrList[0].port);
   //��ֵ��Ϻ���սṹ��
   bzero(&clientAddr,0);
    m++;
   }else{
   	printf("�ͻ�������������������\n");
   	break;
   }
   
   
   pid=fork();
   if(pid==0){
   	//�����ӽ���
   	Close(lfd); //�ӽ�������������رռ����׽���
   	break;
   }else if(pid>0){
   	//���븸����
   	//����������Ҫ���ľ���ע�Ჶ׽���������ӽ���
   	struct sigaction act;
   	act.sa_flags=0;
   	act.sa_handler=waitchild;
   	//������������������źż�
   	sigemptyset(&act.sa_mask);
   	ret=sigaction(SIGCHLD,&act,NULL);
    Close(cfd); //����������ͨ����˹ر���ͻ��˵�ͨ�ŵ��׽���
   	continue;
   }else{
		perror("fork error");
   	exit(1);
   } 
  } 
  
  if(pid==0)
   {  	
   	 //�����ӽ��� 
   	 while(1){   			  	        
		   	int len=read(cfd,buf,sizeof(buf)); //��ȡ�ӽ��̷��͵�����
		   	if(len==0){
		   	    //˵���Ѿ������ļ�ĩβ��
		   	    printf("�Զ˹ر�����");
		   	    exit(1);
		   	}
		   	//���Сдת���ɴ�д
		   	for(int i=0;i<len;i++)
		   	{
		   		buf[i]=toupper(buf[i]);
		   	}
		   	//д��ȥ���ͻ���
		   	write(cfd,buf,len);
		   	write(STDOUT_FILENO,buf,len);
     }   
     Close(cfd);
     return 0;
   }
  

  return 0;
}

