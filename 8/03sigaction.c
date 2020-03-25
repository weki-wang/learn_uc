// 该文件主要测试带参信号处理sigaction函数和sigqueue函数的功能
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
#include <pwd.h>
// 收到SIGUSR2信号后的处理函数
void func(int sig, siginfo_t *sig_info, void *p){
    struct passwd * pd = getpwuid(sig_info->si_uid);
    printf("信号是由进程为%d传递的， 用户为%s \n", sig_info->si_pid, pd->pw_name);
    printf("信号传递的额外参数为%d \n",sig_info->si_value.sival_int);
}

int main()
{
    // 初始化sigaction的参数
    struct sigaction sig_act, sig_old_act;
    sig_act.sa_sigaction = func; // 设置带参信号处理函数
    sigemptyset(&sig_act.sa_mask); // 信号处理函数执行期间不需要屏蔽任何信号
    sig_act.sa_flags = SA_SIGINFO; // 设置sigaction调用sa_sigaction函数处理信号
    sigaction(SIGUSR2, &sig_act, NULL); // 登记信号处理

    // 创建进程并，让子进程给父进程发送信号
    if(fork() == 0){
        // 子进程发送信号
        union sigval v;
        v.sival_int = 2020; // 设置需要传递的参数
        sigqueue(getppid(), SIGUSR2, v); // 发送信号和参数
        sleep(1);
        exit(88);
    }else{
        // 父进程收到数据后，进行信号处理
        pause();
        // 信号处理完成，回收线程资源
        int s;
        waitpid(0, &s, 0);
        printf("子进程已经结束，返回值为%d \n", WEXITSTATUS(s));
        exit(0);
    }
}