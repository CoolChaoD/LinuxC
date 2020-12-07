//写端
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

struct Person{
  int id;
  char name[256];
  int age; 
};

int main()
{
  int fd;
  struct Person* p;
  struct Person person={0,"xiaoming",18};
  int num=sizeof(person); //共享映射区的大小
  fd=open("./12_mmp.txt",O_RDWR|O_CREAT,0644);
  if(fd==-1)
  {
    perror("open error");
    exit(1);
  }
  ftruncate(fd,num); //拓展文件的大小
  p=mmap(NULL,num,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0); //创建共享映射区
  if(p==MAP_FAILED)
  {
     perror("mmap error");
     exit(1);
  }
  close(fd); //创建共享映射区后就可以关闭文件描述符
  
  while(1)
  {
    memcpy(p,&person,sizeof(person));
    person.id++;
    sleep(1);
  }

  munmap(p,num);
  return 0;
}
