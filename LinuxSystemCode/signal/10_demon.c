/*
 * 创建守护进程
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void sys_err(const char* str)
{
  perror(str);
  exit(1);
}
int main()
{
  //1.创建子进程，然后让父进程退出
  pid_t pid;
  int ret,fd;
  pid=fork();
  if(pid>0)
    exit(0);
  //2.子进程创建会话
  pid=setsid();
  if(pid==-1)
  {
    sys_err("setsid error");
  }
  //3.改变文件访问权限掩码
  umask(0022);

  //4.关闭文件描述符0
  close(STDIN_FILENO);
  fd=open("/dev/null",O_RDWR);
  if(fd==-1)
  {
    sys_err("open error");
  }
  dup2(fd,STDOUT_FILENO);
  dup2(fd,STDERR_FILENO);

  //5.改变工作目录位置
  ret=chdir("/home/dongchao/");
  if(ret==-1)
  {
    sys_err("chdir error");
  }

  while(1); //模拟 守护进程任务
  
  return 0;
}


