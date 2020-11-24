#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include<sys/mman.h>


void sys_err(const char* str)
{
  perror(str);
  exit(1);
}

int main()
{
  char *p=NULL; //
  int fd;

  fd =open("testmap",O_RDWR|O_CREAT|O_TRUNC,0644);
  if(fd==-1)
  {
    sys_err("open error");
    exit(1);
  }

  //利用truncate函数进行拓展
  ftruncate(fd,10);//将文件拓展成10字节大小
  int len=lseek(fd,0,SEEK_END); //获取文件的大小

  p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    sys_err("mmap error");

  }
  //使用p对文件进行读写操作
  strcpy(p,"hello world"); //对文件进行写操作
  printf("---%s\n",p);//对文件进行读操作
  return 0;
}
