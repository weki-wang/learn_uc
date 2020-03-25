#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char *argv[])
{
    pid_t id= getpid();
    printf("pid is %d \n", id);
    int i = fork();
    if (i == -1)
        perror("fork error : ");
    else if (i == 0){
        printf("我是子进程。。。 ");
        printf(" 我的id是%d , 我的父进程是%d \n", getpid(), getppid());
    }
    else{
        printf("我是父进程。。。");
        printf("我的id是%d , 我的父进程是%d \n",getpid(), getppid());
    }
    puts("hello");
    return 0;
}