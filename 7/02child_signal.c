#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
// 信号函数的处理
void func(int sig){
    int info;
    pid_t child_pid;
    while( (child_pid = waitpid(-1,&info, WNOHANG)) > 0)
        printf("子进程%d结束，返回值为%d,已回收其资源. \n ", child_pid, WEXITSTATUS(info));
}

int main()
{
    system("clear");
    printf("我的进程是%d, 我将产出10个子进程 \n", getpid());
    // 登记子进程结束信号的调用函数
    signal(SIGCHLD, func);
    for(int j = 0; j < 10; j++){
        // 产出10个子进程
        char ch = 'a' + j;
        if(fork() == 0){
         // 子进程进行循环打字母
            printf("我是子进程，id为%d \n", getpid());
            for(int k = 0; k < 20; k++){
                write(STDERR_FILENO, &ch, sizeof(ch));
                usleep(1000*500);
            }
            exit(ch);
        }
    }
    // 父进程fork结束后，循环休眠100s
    while(1){
        sleep(100);
    }
    return 0;
}