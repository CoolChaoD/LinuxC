#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

void sys_err(const char *str)
{
  perror(str);
  exit(1);
}

int main()
{
  pid_t pid;
  int fd;
  int *p;

  //首先打开一个文件
  fd=open("./mmap.txt",O_RDWR|O_TRUNC);
  if(fd<0)
  {
    sys_err(ZZ)
  }
  p=mmap(NULL,4,)
}
