#include "common.h"

//�����������IP��ַ
#define SERV_IP "47.96.255.54" 
#define SERV_PORT 6666

int main(void)
{
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
	connect(nfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	
	while(1){
		//�ӱ�׼�����л�ȡ����
		fgets(buf,sizeof(buf),stdin);
		//������д��������
		write(nfd,buf,strlen(buf));
		//�ӷ�������ȡ���ݷ��ظ�������
		len=read(nfd,buf,sizeof(buf));
		//д����׼���
		write(STDOUT_FILENO,buf,len);
	}
	
	//�ر�����
	close(nfd);
	return  0;
}