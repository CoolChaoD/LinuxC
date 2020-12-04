/*
 * 使用execlp函数调用date
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
  pid_t pid =fork(); //利用fork先创建一个子进程
  if(pid<0)
  {
    perror("fork error");
    exit(1);
  }else if(pid==0){ //子进程
     execlp("date","date",NULL); //这里的第一个date代表命令的名称，第二个date代表argv[0]
     perror("execlp error"); //如果execlp调用成功的话，那么一下两行就不会执行了
     exit(1);
  }else if(pid>0){ //父进程
    sleep(1);//让子进程先执行完
    printf("I am the parent process,my id is %d\n",getpid());
  }

  return 0;


}

