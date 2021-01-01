#include "common.h"

//�����������IP��ַ
#define SERV_IP "127.0.0.1" 
#define SERV_PORT 6666


int main(void)
{
	pid_t pid; //�ͻ�����Ҫ����������һ��������ȡһ����������
	int nfd,len;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];
	
	//����һ��socket ָ��IPV4 ����TCP����������
	nfd=socket(AF_INET,SOCK_STREAM,0);
	
	//��ʼ����ַ�ṹ
	bzero(&serv_addr,sizeof(serv_addr));  //����
	serv_addr.sin_family=AF_INET;   //IPV4
	//��IP��ַ���ַ�������ת���������ֽ��򣬲���3 �Ǵ�������
	inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
	//���˿ںŴ������ֽ���ת���������ֽ���
	serv_addr.sin_port=htons(SERV_PORT);
	//���ݵ�ַ�ṹ����ָ��������
	Connect(nfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	//���շ������ĵ�ַ��д����ʾ��Ļ��
	struct IPAddr clientRecv;
	char cli_IP[1024];
	len=read(nfd,buf,sizeof(buf));
	memcpy(&clientRecv,buf,len);
	//printf("client IP:%s:Port:%d\n",inet_ntop(AF_INET,&clientRecv.IP,cli_IP,sizeof(cli_IP)),ntohs(clientRecv.port));
	printf("MyIP:%s:Port:%d\n",clientRecv.IP,clientRecv.port);
	pid=fork(); //fork������һ���ӽ���
	if(pid>0)
	{
		//˵�������˸����̣������������������ݸ��ͻ���
		while(1)
		{
			//�ӱ�׼�����л�ȡ����
			fgets(buf,sizeof(buf),stdin);
			//������д��������
			write(nfd,buf,strlen(buf));
	  }
	}else if(pid==0){
		//�����ӽ���
		while(1)
		{
			//ѭ���������������͹�������Ϣ
			len=read(nfd,buf,sizeof(buf));
			write(STDOUT_FILENO,buf,len);//���ӷ������Ͻ��յ�����Ϣ���������ʾ����
		}
	}else{
		perror("fork error");
		exit(1);
	}
	//�ر�����
	Close(nfd);
	return  0;
}