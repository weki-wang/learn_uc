// 用于测试select多路io
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(void)
{
    mkfifo("pipe1", 0644);
    mkfifo("pipe2", 0644);
    int fd1 = open("pipe1", O_RDWR);
    int fd2 = open("pipe2", O_RDWR);
    printf("fd1 is %x fd2 is %x \n", fd1, fd2);
    fd_set fds;
    struct timeval timeout = {0, 0}; // 设置select为不等待
    while(1){
        // 注意使用，每次循环都是先清0，然后添加IO，最后检测
        FD_ZERO(&fds);
        FD_SET(fd1, &fds);
        FD_SET(fd2, &fds);
        FD_SET(STDIN_FILENO, &fds);
        char buf[1000];
        if(select(fd2+1, &fds, NULL, NULL, &timeout) > 0){
            for(int i = 0; i < 16; i++)
                printf("now fds[%d] is %lx \n", i,fds.__fds_bits[i]);
            if(FD_ISSET(0, &fds)){
                scanf(" %[^\n]", buf);
                if(strcmp(buf, "quit") == 0)
                    break;
                puts(buf);
            }
            if(FD_ISSET(fd1, &fds)){
                int n = read(fd1, buf, sizeof(buf)-1);
                buf[n] = '\0';
                printf("pipe1:%s", buf);
            }
            if(FD_ISSET(fd2, &fds)){
                int n = read(fd2, buf, sizeof(buf)-1);
                buf[n] = '\0';
                printf("pipe2:%s", buf);
            }
        }       
    }
    close(fd1);
    close(fd2);
    unlink("pipe1");
    unlink("pipe2");
    return 0;
}