/*************************************************************************
	> File Name: zoom.c
	> Author: ChaoD
	> Mail: 2978651233@qq.com 
	> Created Time: 2020年11月08日 星期日 19时41分07秒
 ************************************************************************/
//学习僵尸进程
//父进程没有死亡但是子进程却死亡了
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid,wpid;
	pid=fork();
	int status;

	if(pid==0){
		printf("------child,myparent =%d,going to sleep 10s\n",getppid());
		sleep(10);
		printf("-----------------------------child die----------------\n");
	}else if(pid>0){
		wpid=wait(&status);
		if(wpid==-1){
		  perror("wait error");
		  _exit(1);
		}
		printf("------------parent wait finish---------------------------\n");
               
	}else{
	
		perror("fork");
		return 1;
	}

	return 0;
}
