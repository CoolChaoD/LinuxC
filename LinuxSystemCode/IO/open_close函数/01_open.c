#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{

  int fd=open("./test",O_WRONLY);
  if(fd==-1) 
  {
    perror("open error\n");
  }
//  printf("fd=%d,errno=%d:%s\n",fd,errno,strerror(errno));
  close(fd);
  return 0;
}
