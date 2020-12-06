//读端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void sys_err(const char *str)
{
  perror(str);
  exit(1);
}

int main()
{
  int len;
  char buf[4096];
  int fd=open("./10_myfifo",O_RDONLY);
  if(fd==-1)
  {
    sys_err("open error");
  }
  while(1)  //循环将读取的数据写到平面镜上去
  {

    len=read(fd,buf,sizeof(buf));
    if(len<0)
    {
      sys_err("read error");
      exit(1);
    }
    write(STDOUT_FILENO,buf,len);
  }
  return 0;
}


