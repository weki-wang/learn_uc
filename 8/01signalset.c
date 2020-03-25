#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    sigset_t ss;
    sigemptyset(&ss); // 清空信号集
    puts(sigismember(&ss,SIGINT)?"have sigint":"no sigint");
    sleep(5);
    sigaddset(&ss, SIGINT);
    puts(sigismember(&ss,SIGINT)?"have sigint":"no sigint");
    sleep(5);
    sigdelset(&ss, SIGINT);
    puts(sigismember(&ss,SIGINT)?"have sigint":"no sigint");
    sleep(5);
    sigfillset(&ss);
    puts(sigismember(&ss,SIGINT)?"have sigint":"no sigint");
    return 0;
}