/*
 * 利用mmap创建映射区实现非血缘关系的进程通信
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

//读端 
struct Person{
  int id;
  char name[256];
  int age; 
};

int main()
{
  int fd;
  struct Person* p; //创建一个结构体指针
  struct Person person;
  fd =open("./12_mmp.txt",O_RDONLY);
  p=mmap(NULL,sizeof(person),PROT_READ,MAP_SHARED,fd,0);
  if(p==MAP_FAILED)
  {
    perror("mmap error");
    exit(1);
  }
  close(fd);
  while(1)
  {
    printf("id=%d,name=%s,age=%d\n",p->id,p->name,p->age);
    sleep(1);
  }
  munmap(p,sizeof(person));
  return 0;
}
