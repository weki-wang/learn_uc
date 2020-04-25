// 该文件为本地网络通讯的客户端，配合08文件使用
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <linux/tcp.h>
#include <signal.h>
#include <unistd.h>

typedef struct sockaddr * sa;
void func(int sig){
    // 
    printf("reciev SIGPIPE signal...\n");
}

int main()
{
    // 注册信号
    signal(SIGPIPE, func);
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un sau;
    sau.sun_family = AF_LOCAL;
    strcpy(sau.sun_path , "socket_local_file");
    socklen_t len = sizeof(sau);
    if(connect(fd, (sa)&sau, len) < 0 ){
        perror("connect failed");
        exit(-1);
    }
    char rec_msg[1024];
    while(1){
        int n = read(fd, rec_msg, sizeof(rec_msg)-1);
        if( n <= 0)
            break;
        rec_msg[n] = '\0';
        puts(rec_msg);
    }
    puts("再见...");
    close(fd);
}