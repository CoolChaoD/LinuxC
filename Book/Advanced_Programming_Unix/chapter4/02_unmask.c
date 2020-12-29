#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

void perr_exit(const char *str)
{
	perror(str);
	exit(1);
}

int main()
{
	umask(0);
	int n;
	n=creat("test1",RWRWRW);
	if(n<0)
	{
			perr_exit("creat test1 error");
	}
	//禁止所有组和其他用户访问文件
	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	n=creat("test2",RWRWRW);
	if(n<0)
	{
			perr_exit("creat test2 error");
	}
return 0;
}
