/*************************************************************************
	> File Name: fork.cpp
	> Author: ChaoD
	> Mail: 2978651233@qq.com 
	> Created Time: 2020年11月04日 星期三 13时44分38秒
 ************************************************************************/
#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdio.h>

int main(){
	pid_t fpid;
	int count=0;
	fpid=fork(); //返回子进程的ID
	if(fpid<0){  //如果返回负数，则出错了
		cout<<"failed to fork";
	
	}
	else if(fpid==0){
	cout<<"I am the child process,my pid is "<<getpid()<<endl;
	count++;
	}
	else //如果fork的值大于0，则依旧在父进程中执行
	{
	  cout<<"I am the parent process,my pid is "<<getpid()<<endl;
	  cout<<"fpid="<<fpid<<endl;
	  count++;
	}

}

