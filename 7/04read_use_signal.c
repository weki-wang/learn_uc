#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
void func(int sig){
    int fd = open("data",O_RDONLY);
    if(fd < 0) return ;
    char buf[100];
    int read_num = read(fd, buf, sizeof(buf));
    if (read_num > 0)
        buf[read_num] = '\0';
    puts(buf);
    close(fd);
    unlink("data");
}

int main()
{
    signal(SIGUSR1, func);
    printf("我的进程ID为: %d \n", getpid());
    while(1){
        sleep(100);
    }
}