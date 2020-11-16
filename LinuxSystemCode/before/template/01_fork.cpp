/*************************************************************************
	> File Name: fork.cpp
	> Author: ChaoD
	> Mail: 2978651233@qq.com 
	> Created Time: 2020年11月04日 星期三 21时44分01秒
 ************************************************************************/
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(){
	printf("before fork-1-\n");
	printf("before fork-2-\n");
	printf("before fork-3-\n");
	printf("before fork-4-\n");
	pid_t pid=fork();
	if(pid==-1){
		perror("fork error");
		exit(1); //异常退出
	}else if(pid==0){
		printf("--child is created\n");

	}else if(pid>0){
	 printf("---parent process: my child is %d\n",pid);

	}
	printf("================end of file\n");
	return 0;


