//练习mmap的使用
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void sys_err(const char* str)
{
   perror(str);
   exit(1);
}


int main()
{
  int fd;
  char* p=NULL;

  fd =open("testmap",O_RDWR|O_CREAT|O_TRUNC,0644);

  ftruncate(fd,10);//将文件拓展成10字节大小
  int len=lseek(fd,0,SEEK_END); //获取文件的大小

  p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
   sys_err("mmap error");

  }

  strcpy(p,"hello world");
  printf("---%s\n",p);
  close(fd);

  int ret=munmap(p,len);
  if(ret==-1)
  {
    sys_err("munmap error");
  }
  return 0;
}
