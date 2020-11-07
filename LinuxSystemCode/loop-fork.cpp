#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
        int i;
        for(i=0;i<5;i++){
                if(fork()==0){
                   break;
                }
        }
        if(5==i){
              sleep(5);
                printf("I am parent \n");
        }else{

              sleep(i);
              printf("I am %dth child\n",i+1);
        }
        return 0;
}
