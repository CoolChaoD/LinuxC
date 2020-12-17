/*
 * 增强版的select增加了一个数组
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

#include "wrap.h"

#define SERV_PORT 6666 

int main()
{
  int i,j,n,maxi;

  int nready,client[FD_SETSIZE]; //自定义数组client,防止遍历1024个文件描述符， FD_SETSIZE默认为1024
  int maxfd,listenfd,connfd,sockfd;
  char bufsize[BUFSIZ],str[INET_ADDRSTRLEN];
}
