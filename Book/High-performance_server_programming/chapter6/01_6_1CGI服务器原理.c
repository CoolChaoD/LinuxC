#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define PORT 6666 //定义服务器的端口号6666

int main()
{
  struct sockaddr_in server_addr; //定义服务器的地址
  bzero(&server_addr,sizeof(server_addr)); //将服务器的IP地址清空
  server_addr.sin_family=AF_INET; //IPV4
  server_addr.sin_port=htons(PORT);
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY); 

  int lfd=socket(AF_INET,SOCK_STREAM,0);
  assert(lfd>=0);

  int ret=bind(lfd,(struct sockaddr*)&server_addr,sizeof(server_addr));

  ret=listen(lfd,5); 
  assert(ret!=-1);

  struct sockaddr_in client;
  socklen_t client_addrlength =sizeof(client);

  int connfd =accept(lfd,(struct sockaddr*)&client,&client_addrlength);
  if(connfd<0)
  {
    perror("accept error");
    exit(1);
  }
  else
  {
    close(STDOUT_FILENO);
    dup(connfd);
    printf("abcd");
    close(connfd);
  }

close(lfd);
return 0;
}
