#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define NUM 1024
void sys_err(const char *str)
{
  perror(str);
  exit(1);
}

int main()
{
  pid_t pid;
  int fd;
  char *p;

  //首先打开一个文件
  fd=open("./mmap.txt",O_RDWR|O_CREAT);
  if(fd<0)
  {
    sys_err("open error");
  }
  ftruncate(fd,NUM); //拓展文件的大小
  p=mmap(NULL,NUM,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    sys_err("mmap error");
  }
  //建立映射区完毕后，即可关闭文件
  close(fd);
  pid=fork(); //fork创建子进程
  if(pid==0)  //子进程
  {
    strcpy(p,"hello pipe"); //对文件进行写操作
  }else if(pid>0){ //进入了父进程
    printf("-----%s\n",p); //共享内存
    wait(NULL); //回收子进程
    int ret=munmap(p,NUM);  //释放映射区
    if(ret==-1)
    {
      sys_err("munmap error");
    } 
    return 0;
  }
}
