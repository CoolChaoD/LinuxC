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
	char buf[4096];
	int i;
	//���ڴ洢�ͻ��˵�IP��ַ
	char cli_IP[1024];
  Message recvMessage;
  struct IPAddr clientAddr;
  
  
  
  //���������ڴ�ӳ��
  Message *p;
  int fd;
  //��һ���ļ�
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
  Close(fd); //�����ڴ�ӳ����������Ϻ���Թر��ļ�������

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
   
   strncpy(clientAddr.IP,cli_IP,strlen(cli_IP));
   clientAddr.port=ntohs(cli_addr.sin_port);   
   
   memset(buf,0,1024); //��buf����
	 memcpy(buf,&clientAddr,sizeof(IPAddr));
	 //printf("child %s:%d\n",clientAddr.IP,clientAddr.port);
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
   }else
{

		
perror("fork error");
   	exit(1);
   } 
  } 
  
  if(pid==0)
   {  	
   	 IPAddr myAddr;
   	 IPAddr recvAddr;
   	 myAddr=clientAddr; //ÿһ���ӽ����ж���һ����ַ�ṹ�洢���Լ��ĵ�ַ�ṹ
   	 //printf("I am a child process for %s:%d\n",myAddr.IP,myAddr.port);
   	 //�����ӽ��� 
   	 for(;;){    
   	 	  	 	 	 		
		    if(recvAddr.IP==myAddr.IP&&recvAddr.port==myAddr.port)
		    {
		    	  printf("match correct");
		    }
		     	  	        
		   	int len=read(cfd,buf,sizeof(buf)); //��ȡ�ӽ��̷��͵�����
		   	if(len==0){
		   	    //˵���Ѿ������ļ�ĩβ��
		   	    printf("�Զ˹ر�����");
		   	    exit(1);
		   	}
        //memcpy(&recvMessage,buf,len);
        //printf("from client:\n");
        //printf("%s:%d,data:%s\n",recvMessage.ipaddr.IP,recvMessage.ipaddr.port,recvMessage.buf);
		    memcpy(p,buf,len);
        recvAddr=p->ipaddr;
        
		    printf("%s:%d,data:%s\n:",p->ipaddr.IP,p->ipaddr.port,p->buf);
		  
     }   
   }
  return 0;
}

