#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main()
{
  int fd =open("./test.txt",O_RDWR|O_CREAT,0644);
  if(fd==-1)
  {
    perror("open error");
  }
  int newfd=fcntl(fd,F_DUPFD,5); //将5号文件描述符重定向到fd
  printf("newfd=%d\n",newfd);
  int ret= write(newfd,"test",4);
  printf("ret=%d\n",ret);
  return 0; 
}

