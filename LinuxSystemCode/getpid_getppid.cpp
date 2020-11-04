/*************************************************************************
	> File Name: getpid_getppid.cpp
	> Author: ChaoD
	> Mail: 2978651233@qq.com 
	> Created Time: 2020年11月04日 星期三 22时33分45秒
 ************************************************************************/
#include <unistd.h>
#include <string.h>
#include <cstdio>

int main(){
	printf("before fork\n");
	pid_t pid=fork();
	if(pid==-1){
	   perror("fork error");
	   _exit;
	}
	if(pid==0){
	   printf("---child is created,pid=%d,parent-pid=%d\n",getpid(),getppid());
	}else if(pid>0){
	  printf("---parent process:my child is %d,my pid is %d, my parent pid is %d\n",pid,getpid(),getppid());
	}
	printf("=============end of file\n");
	return 0;
}
