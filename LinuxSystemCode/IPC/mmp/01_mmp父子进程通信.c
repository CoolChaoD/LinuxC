#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

int var =100;

int main()
{
  int *p;
  pid_t pid;

  int fd;
  fd =open("temp",O_RDWR|O_CREAT|O_TRUNC,0644);
  if(fd<0)
  {
    perror("open error");
    exit(1);
  }
  ftruncate(fd,4);

  p=mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    perror("mmp error");
    exit(1);
  }
  close(fd);//建立映射区完毕即可关系文件
  pid =fork();
  if(pid==0){ //进入子进程
    *p=1119;//向文件里面写东西
    var=10000;
    printf("child,*p=%d,var=%d\n",*p,var);
  }else{//进入父进程
    sleep(1);
    printf("parent,*p=%d,var=%d\n",*p,var); //读共享内存
    wait(NULL);

    int ret=munmap(p,4);
    if(ret==-1)
    {
      perror("munmap error");
      exit(1);
    }
  }
  return 0;
}

