#include <signal.h>
#include <stdio.h>
#include <unistd.h>
// 信号处理函数
void func(int sig){
    switch (sig)
    {
    case SIGINT :
        puts("我不怕Ctrl+C， 我不会结束");
        break;
    case SIGTERM :
        puts("我不怕kill，我不会结束");
        break;
    case SIGTSTP :
        puts("我不怕Ctrl+Z, 我是不会停");
        break;    
    default:
        break;
    }
}

int main()
{
    signal(SIGTSTP, func);
    signal(SIGINT, func);
    signal(SIGTERM, func);

    printf("我的pid是 %d, 来停止我呀! \n", getpid());
    while(1){
        write(STDERR_FILENO, "." , 1);
        usleep(1000000 * 10);
    }
}