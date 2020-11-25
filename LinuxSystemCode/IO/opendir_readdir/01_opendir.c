//本案例用来练习opendir/closedir/readdir
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc,char *argv[])
{
  DIR *dp;
  struct dirent *sdp;

  //打开一个文件目录
  dp=opendir(argv[1]);
  if(dp==NULL)
  {
    perror("opendir error");
    exit(1);
  }
  while((sdp=readdir(dp))!=NULL)
  {
    if(strcmp(sdp->d_name,".")==0)
    {
      continue;
    }else if(strcmp(sdp->d_name,"..")==0)
    {
      continue;
    }
    printf("%s\t",sdp->d_name);
  }
  printf("\n");
  closedir(dp);
  return 0;
}
