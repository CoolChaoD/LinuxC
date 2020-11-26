#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main()
{
  int fd =open("test",O_RDWR|O_CREAT,0644);

  if(fd==-1)
  {
    perror("open error");
    exit(1);
  }
  int length=lseek(fd,99,SEEK_END); //从文件末尾开始向后拓展99个字节
  write(fd,"\0",1);
  printf("file size=%d\n",length);
  close(fd);
  return 0;
}
