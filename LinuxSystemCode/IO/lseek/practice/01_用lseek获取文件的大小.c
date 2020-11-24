#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
  int fd=open(argv[1],O_RDWR);

  int length=lseek(fd,100,SEEK_END);
  write(fd,"\0",1);
  printf("文件的大小为%d\n",length);

  close(fd);
  return 0;
}
