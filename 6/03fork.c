#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    if(fork()==0){
        for(int i = 0; i < 3; i++){
            printf("我是子进程。 我的id为%d , 父进程id为%d \n",getpid(), getppid());
            sleep(1);
        }
    }
    else{
        for(int j = 0; j < 10; j++){
            printf("我是父进程。\n");
            sleep(1);
        }
    }
    return 0;
}