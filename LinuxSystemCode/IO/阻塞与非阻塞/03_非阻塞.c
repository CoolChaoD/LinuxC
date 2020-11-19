#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
  char buf[10];
  int n;
  int fd;
  int i;
  fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
  if(fd<0)
  {
    perror("open error");
    exit(1);
  }
  printf("open dev/tty ok...%d",fd);

  for(i=0;i<5;i++)
  {
     n=read(fd,buf,10);

     if(n>0)
     {
       break;           //说明读到了东西
     }
     if(errno!=EAGAIN)
     {
       perror("read dev/tty");
       exit(1);
     }else{
       write(STDOUT_FILENO,"try again\n",strlen("try again\n"));
       sleep(2);
     }
      
  }
  if(i==5)
  {
    write(STDOUT_FILENO,"time out\n",strlen("time out\n"));

  }else{

    write(STDOUT_FILENO,buf,n);
  }
  close(fd);

  return 0;
}


