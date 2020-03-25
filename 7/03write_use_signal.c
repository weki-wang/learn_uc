#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
int main()
{
    pid_t who;
    printf("请输入对方的进程id： ");
    scanf("%d", &who);
    char buf[100];
    while(1){
        printf("inupt:");
        scanf(" %[^\n]",buf);
        int fd;
        while(1){
            fd = open("data", O_WRONLY|O_CREAT|O_EXCL, 0666);
            if (fd > 0) break;
            puts("data文件已存在");
            sleep(1);
        }
        write(fd, buf, strlen(buf));
        close(fd);
        kill(who, SIGUSR1);
    }
}