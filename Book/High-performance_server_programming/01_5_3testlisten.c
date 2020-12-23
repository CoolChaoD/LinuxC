#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static bool stop =false;

static void handle_term(int sig)
{
  stop=true;
}

int main(int argc,char *argv[])
{
  signal(SIGTERM,handle_term); //当收到SIGTERM信号后stop立即变成true
  if(argc<=3) //说明输入的参数小于3个。这是时候提示报错
  {
    printf("usage:%s ip_address port_number backlog");
    return(1);
  }
  const char* ip=argv[1];
  int port=atoi(argv[2]);
  int backlog=atoi(argv[3]);
  
  int listenfd=socket(PF_INET,SOCK_STREAM,0);
  assert(listenfd>=0);

  //创建一个ipv4的 socket地址
  struct sockaddr_in address;
  bzero(&address,szieof(address));
  address.sin_family=AF_INET;

}





