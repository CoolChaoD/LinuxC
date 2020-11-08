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
	pid_t pid;
	pid=fork();

	if(pid==0){
		printf("------child,myparent =%d,going to sleep 10s\n",getppid());
		sleep(10);
		printf("-----------------------------child die----------------");
	}else if(pid>0){
		while(1){
		 printf("I am parent,pid=%d,myson =%d\n",getpid(),pid);
		 sleep(1);
		}
	}else{
	
		perror("fork");
		return 1;
	}

	return 0;
}
