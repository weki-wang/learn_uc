/* 创建一个服务器，用于聊天，综合运用了线程、socket等相关知识 */
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <netdb.h> /*gethostbyname */

#define MAX_CLIENT_NUM 5
typedef struct client_ip4
{
    int fd;
    char ip[16];
}client;
client client_fds[MAX_CLIENT_NUM];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* 该函数接受一个字符串，然后将该字符串发送至所有客户端*/
void BroadCast(int myself_fd, const char *msg, client *clients){
    // 向剩余的其他客户端发送信息
    int i ;
    pthread_mutex_lock(&lock);
    for(i = 0; i < MAX_CLIENT_NUM; i++){
        if((clients+i)->fd != 0 &&  (clients+i)->fd != myself_fd )
            write((clients+i)->fd, msg, strlen(msg));
    }
    pthread_mutex_unlock(&lock);
}


/* 用于获取本地IP的函数并写入ip中，成功返回0，失败返回-1*/
int GetLocalIp(struct in_addr *ip){
    char name[256];
    if(gethostname(name, sizeof(name)) < 0){
        perror("gethostname failed");
        return -1;
    }
    struct hostent *hn;
    hn = gethostbyname(name);
    if(hn == NULL){
        herror("gethostbyname failed");
        return -1;
    }
    ip->s_addr =  ((struct in_addr *)(hn->h_addr_list[0]))->s_addr; 
    return 0;
}

/* 辅助线程的运行函数 */
void * func(void * arg){
    pthread_mutex_lock(&lock);
    client s = *(client *)arg;
    pthread_mutex_unlock(&lock);
    // 首先向其他所有客户端发送信号，欢迎用户xx的到来
    char msg[1024];
    sprintf(msg, "欢迎IP为%s，编号为%d的用户进入wechat聊天室... \n", s.ip, s.fd);
    BroadCast(s.fd ,msg, client_fds);
    while(1){
        // 循环读取用户的输入，然后发送至其他用户
        char temp[512];
        int n = read(s.fd, temp, sizeof(temp)-1); 
        if(n<0) 
            break;
        if( strncmp(temp, "quit\r\n", n) == 0){ // 注意，网络通讯中一般是以\r\n结束,在这里的对比需要注意
            printf("退出.. \n");
            break;
        }
        temp[n] = '\0';
        sprintf(msg,"IP为%s，编号为%d的用户:%s", s.ip, s.fd, temp);
        BroadCast(s.fd ,msg, client_fds);
    }
    close(s.fd);
    ((client *)arg)->fd = 0;
    return NULL;
}

int main(void)
{
    /*获取本机IP地址，用于创建服务器 */
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in si;
    si.sin_family = AF_INET;
    si.sin_port = htons(5656);
    if(GetLocalIp(&si.sin_addr) < 0)
        exit(-1);
    if(bind(fd,(struct sockaddr *)&si, sizeof(si))<0){
        perror("bind failed");
        exit(-1);
    }
    /* 创建多线程，主线程用于监听服务的连接，其他辅助线程用于收发各个用户输入的数据 */
    listen(fd, 10);
    printf("服务器创建成功，IP为%s, 端口为%d. \n", inet_ntoa(si.sin_addr), ntohs(si.sin_port));
    while(1){
        socklen_t len = sizeof(si);
        int fd_new = accept(fd, (struct sockaddr *)&si, &len);
        if(fd_new < 0) 
            continue;
        /* 判断客户端是否已经满了 */
        int n ;
        for(n = 0; n < MAX_CLIENT_NUM ; n++){
            if (client_fds[n].fd == 0)
                break;
        }
        if(n == MAX_CLIENT_NUM){
            puts("当前用户连接数已满，请稍后再连接wechat...");
            close(fd_new);
            continue;
        }
        else{
            /* 如果没有满，则创建新线程，用于读写该用户的输入内容 */
            printf("目前连接数为%d,分给用户的编号为%d \n", n, fd_new);
            pthread_mutex_lock(&lock);
            client_fds[n].fd = fd_new;
            inet_ntop(AF_INET, &(si.sin_addr), client_fds[n].ip, 16);
            pthread_t thread_id;
            pthread_create(&thread_id, NULL, func, (void *)(&client_fds[n]));
            pthread_mutex_unlock(&lock);
        }
    }
}