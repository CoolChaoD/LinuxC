#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void sys_err(const char *str)
{
  perror(str);
  exit(1);
}

int main()
{
  int fd,len,i;
  char buf[4096];

  fd=open("./10_myfifo",O_WRONLY);
  if(fd<0)
  {
    sys_err("open error");
    exit(1);
  }

  i=0;
  while(1)
  {
    sprintf(buf,"hello fifo%d\n",i++);
    write(fd,buf,strlen(buf));
    sleep(1);
  }
  close(fd);
  return 0;
}
