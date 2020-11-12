#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(){
  pid_t pid;
  int i=0;
  for(i=0;i<5;i++){
    pid=fork();
    if(pid==0){
      break;

    }
  }
  if(i==5){
    printf("I am parent process\n");
  }
  else{
    printf("I am %dth child process\n",i+1);
  }

return 0;
}
