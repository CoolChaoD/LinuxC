#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

int  main(int argc,char *argv[])
{
  char buf[1024];
  int n=0;
  int fd1=open(argv[1],O_RDONLY);//打一个file1
  if(fd1==-1)
  {
    perror("open argv1 error");
    exit(1);
  }
  int fd2=open(argv[2],O_WRONLY);
  if(fd2==-1)
  {
    perror("open argv2 error");
    exit(1);
  }

  //read函数的失败返回-1，成功则返回读取到的字节数，若为0则代表已经读取到文件末尾
  while((n=read(fd1,buf,1024))!=0)
  {
    if(n<0)
    {
      perror("read error");
      break;
    }
    write(fd2,buf,n);
  }

  close(fd1);
  close(fd2);
  return 0;
}
