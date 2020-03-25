// 该文件用于联系信号屏蔽
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
void func(int sig){
    puts("睡觉期间收到了SIGINT信号");
    exit(0);
}

int main()
{
    // 注册信号函数
    signal(SIGINT, func);
    sigset_t newset, oldset;
    // 清空信号集
    sigemptyset(&newset);
    // 设置要阻塞的信号集
    sigaddset(&newset, SIGINT); // CTRL + C
    sigaddset(&newset, SIGTERM); // kill 命令
    // 开启阻塞信号
    sigprocmask(SIG_BLOCK, &newset, &oldset);
    puts("我需要睡觉，不要来打扰我！");
    sleep(10);
    puts("睡醒了");
    // 关闭阻塞集
    sigprocmask(SIG_SETMASK, &oldset, NULL);
    // 重新处理阻塞信号
    puts("睡觉期间没有信号来过"); // 注意，如果在睡眠期间ctrl+c则不会出现这个，因为上面结束阻塞会立即执行ctrl+c
    return 0;
}