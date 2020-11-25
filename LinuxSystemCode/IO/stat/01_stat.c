#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
//stat函数的使用

int main(int argc,char *argv[])
{
  struct stat sb;
  int ret=stat(argv[1],&sb);
  if(ret==-1)
  {
    perror("stat error");
    exit(1);
  }
  printf("file size%ld\n",sb.st_size);
  return 0;
}
