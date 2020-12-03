#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  main()
{
  int i;
  for (i=0;i<5;i++)
  {
     if(fork()==0)
       break;
  }

  if(i==5) //说明进入了父进程当中
  {
    sleep(5);
    printf("我是父进程，进程号是%d\n",getpid());
  } else {
    sleep(i);
    printf("I am %dth child\n",i+1);

  }
  return 0;

}
