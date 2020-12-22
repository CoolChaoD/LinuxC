//查看lseeek学习文件空洞
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void err_sys(const char* str)
{
  perror(str);
  exit(1);
}



int main()
{
  char buf1[]="abcdefghij";
  char buf2[]="ABCDEFGHIJ";

  int fd,offset;
  fd =open("./file.hole",O_RDWR|O_CREAT,0644);
  if(fd<0)
  {
    err_sys("open error");
  }
  write(fd,buf1,10);
  offset=lseek(fd,16384,SEEK_SET);
  if(offset==-1)
  {
    err_sys("lseek error");
  }
  write(fd,buf2,10);
  return 0;
}
