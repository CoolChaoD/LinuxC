//本案例用来学习stat中的宏
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc,char* argv[])
{
  struct stat sb;
  int ret=stat(argv[1],&sb);
  if(ret==-1)
  {
    perror("stat error");
    exit(1);
  }
  if(S_ISREG(sb.st_mode))
  {
    printf("It's a regular\n");
  }else if(S_ISDIR(sb.st_mode))
  {
    printf("It's a dir\n");
  }else if(S_ISFIFO(sb.st_mode))
  {
    printf("It is a fifo\n");
  }
  return 0;
}
