#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    uid_t uid = getuid();
    gid_t gid = getgid();
    printf("start...\n");
    pid_t pid = getpid();
    printf("1...\n");
    pid_t ppid = getppid();
    char name[256];
    int pagsize = getpagesize();
    gethostname(name, 256);
    printf("用户id:%d, 组id:%d, 进程id:%d, 父进程id:%d, 主机名:%s", uid, gid, pid, ppid, name);
    printf("%d",pagsize);
    return 0;
}