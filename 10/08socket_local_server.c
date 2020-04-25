// 该文件用于测试本地网络通讯的服务器，主线程等待连接，当客户端连接超过八个，其他不可以连接
// 辅助线程，用于判断当前的连接个数和状态，并将用户输入的内容，发送至正在连接的客户端上
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/un.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define MAX_CONNECT_CLIENT_NUM 6
typedef struct sockaddr* sa;
pthread_mutex_t lock ;
int client_fds[MAX_CONNECT_CLIENT_NUM];
void func_sig(int sig){
    // 正对SIGPIPE信号不做处理
    ;
}

void *func(void *fds){
    int * client_fd = fds;
    char msg[1024];
    while(1){
        printf("请输入您要广播的内容: ");
        fflush(stdout);
        scanf(" %[^\n]", msg);
        if(strcmp(msg, "quit") == 0)
            break;
        pthread_mutex_lock(&lock);
        int i;
        for(i = 0; i < MAX_CONNECT_CLIENT_NUM; i++){
            // 检测已连接的客户端是否还在连接中,如果没有连接，则将文件描述符清零
            if (*(client_fd+i) == 0)
                continue;
            if( write(*(client_fd+i), msg, strlen(msg)) < 0 ){
                printf("编号为%d的客户端已关闭... \n", *(client_fd+i));
                *(client_fd+i) = 0;
            }
        }
        pthread_mutex_unlock(&lock);
    }
    // 退出
    int i;
    for(i = 0; i < MAX_CONNECT_CLIENT_NUM; i++){
        if (*(client_fd+i) != 0)
            close(*(client_fd+i));
    }
    pthread_mutex_destroy(&lock);
    unlink("socket_local_file");
    exit(0);
}


int main()
{
    signal(SIGPIPE, func_sig);
    // 建立一个本地网络连接的套接字
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un sau;
    sau.sun_family = AF_LOCAL;
    strcpy(sau.sun_path, "socket_local_file");
    // 将套接字和文件描述符绑定
    if(bind(fd, (sa)&sau, sizeof(sau)) < 0){
        perror("bind failed");
        exit(-1);
    }
    // 监听
    listen(fd, 5);
    // 创建辅助线程不断广播一些内容，主线程等待连接
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, func, (void *)&client_fds);
    pthread_mutex_init(&lock, NULL);
    while (1)
    {
        // 首先等待连接
        socklen_t len = sizeof(sau);
        int fd_connect = accept(fd,(sa)&sau, &len);
        if(fd_connect < 0){
            printf("accept failed. wait for next client accept... \n");
            continue;
        }
        int i ;
        pthread_mutex_lock(&lock);
        for(i = 0; i < MAX_CONNECT_CLIENT_NUM; i++){
            if(client_fds[i] != 0)
                continue;
            else{
                char st[256] ;
                sprintf(st, "您好，您的编号是%d，感谢您的收听...", fd_connect); // 会自动追加空字符
                write(fd_connect, st, strlen(st));
                client_fds[i] = fd_connect;
                break;
            }
        }
        if(i == MAX_CONNECT_CLIENT_NUM){
            char st[] = "已连接的客户端已满，请稍后连接...\n";
            write(fd_connect, st, strlen(st));
            close(fd_connect);
        }
        pthread_mutex_unlock(&lock);
    }
    
}