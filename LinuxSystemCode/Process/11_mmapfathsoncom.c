#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

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
  int *p;

  //首先打开一个文件
  fd=open("./mmap.txt",O_RDWR|O_TRUNC);
  if(fd<0)
  {
    sys_err("open error");
  }
  ftruncate("./mmap.txt",NUM); //拓展文件的大小
  p=mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    sys_err("mmap error");
  }

  pid=fork(); //fork创建子进程
  if(pid==0)  //子进程
  {
    strcpy(p,"hello pipe"); //对文件进行写操作
    
  }else if(pid>0){ //进入了父进程
    
    printf("-----%s\n",p);
    wait(NULL); //回收子进程
  }

}
