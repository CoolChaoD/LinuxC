//使用lseek获取文件的大小
//拓展文件的大小,要想真正的拓展文件的大小，必须引起I/O操作
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char* argv[])
{
  int fd=open(argv[1],O_RDWR);
  if(fd==-1)
  {
    perror("open error");
    exit(1);
  }
  int length=lseek(fd,98,SEEK_END);
  printf("file size:%d\n",length);
  write(fd,"a",1);
  close(fd);


  return 0;


}
