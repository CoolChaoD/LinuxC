//sendfile函数在两个文件描述符之间传递数据效率很高(完全是在内核中操作),避免了内核缓冲区和用户缓冲区之间的数据拷贝
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define PORT 6666
int main()
{
  int filefd=open("./file.txt",O_RDONLY); //以只读的方式打开一个文件
  assert(filefd>0);
  struct stat stat_buf;
  fstat(filefd,&stat_buf);

  struct sockaddr_in server_addr;
  bzero(&server_addr,sizeof(server_addr));
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  server_addr.sin_port=htons(PORT);

  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  assert(sockfd>=0);

  int ret=bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  assert(ret!=-1);

  ret=listen(sockfd,5);
  assert(ret!=-1);

  struct sockaddr_in client;
  socklen_t client_addrlength =sizeof(client);
  int connfd=accept(sockfd,(struct sockaddr*)&client,&client_addrlength);
  if(connfd<0)
  {
    perror("accept error");
    exit(1);
  }
  else
  {
    sendfile(connfd,filefd,NULL,stat_buf.st_size);
    close(connfd);
  }

  close(sockfd);
  return 0;
}

