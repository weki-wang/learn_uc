// 该程序用于测试socket的upd通讯，注意upd不太区分服务器，客户端，唯一区别可能是服务器的ip和port已知
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netdb.h> // gethostbyname函数
#include <string.h>

// 获取本地IP地址，并将其储存在结构体sockaddr_in中
// 成功返回0，失败返回-1
int getLocalIp(struct sockaddr_in * s){
    char name[256];
    if(gethostname(name, sizeof(name)) < 0){
        perror("gethostname failed");
        return -1;
    }
    struct hostent *ht;
    printf("%s \n", name);
    ht = gethostbyname(name);
    if(ht == NULL){
        herror("gethostbyname failed");
        return -1;
    }
    // 方式1，结构体的强制转换
    // s->sin_addr.s_addr = ((struct in_addr *)ht->h_addr_list[0])->s_addr;
    // 通过库函数转换,注意 ht->h_addr_list中储存的是二进制整数信息,而不是点分十进制不能使用inet_pton
    inet_ntop(AF_INET, ht->h_addr_list[0], name, sizeof(name));
    inet_aton(name, &(s->sin_addr));


    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("%s Port \n", argv[0]);
        exit(-1);
    }
    // 创建客户端
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    // 绑定 IP 和 Port
    struct sockaddr_in si;
    if(getLocalIp(&si)< 0){
        printf("getLocalIp failed. \n");
        exit(-1);
    }
    si.sin_port = htons(atoi(argv[1]));
    si.sin_family = AF_INET;
    if(bind(s, (struct sockaddr *)(&si), sizeof(si)) < 0){
        perror("bind failed");
        exit(-1);
    }
    printf("UDP客户端/服务器建立完成：IP为%s,端口号为%d \n", inet_ntoa(si.sin_addr), atoi(argv[1]));
    /* s ip port text 发送信息
     * q 退出
     * r 接受信息
     * a text 回复信息
     */
    char msg[1024];
    char ip[16];
    in_port_t port;
    struct sockaddr_in si_new, si_rec;
    int size_si_rec = sizeof(si_rec);
    while(1){
        printf("s发送信息/q退出/r接受/a回复: ");
        fflush(stdout);
        char cmd;
        scanf(" %c", &cmd);
        if (cmd == 'q'){ 
            printf("退出... \n");
            break;
        }else if(cmd == 's'){
            // 发送信息
            printf("请输入一下格式: IP Port 发送的内容 \n");
            scanf(" %s%hd %[^\n]", ip, &port, msg);
            msg[strlen(msg)] = '\0';
            si_new.sin_family = AF_INET;
            if(inet_aton(ip, &(si_new.sin_addr)) == 0){
                printf("Invalid address \n");
                exit(-1);
            }
            si.sin_port = htons(port);
            sendto(s, msg, strlen(msg), 0, (struct sockaddr *)(&si), sizeof(si));
        }else if(cmd == 'r'){
            // 接受信息
            int rec_num = recvfrom(s, msg, sizeof(msg)-1, MSG_DONTWAIT, (struct sockaddr *)(&si_rec), (socklen_t *)&(size_si_rec));
            if(rec_num <= 0){
                printf("receive failed. \n");
                continue ;
            }
            msg[rec_num] = '\0';
            printf("收到来自IP为%s, 端口号为%d的信息:%s \n", inet_ntoa(si_rec.sin_addr), ntohs(si_rec.sin_port), msg);
        }else if(cmd == 'a'){
            // 回复消息
            printf("请输入(向上一次发送消息给我的对象)需要发送的内容: \n");
            scanf(" %[^\n]", msg);
            msg[strlen(msg)] = '\0';
            sendto(s, msg, strlen(msg), 0, (struct sockaddr *)(&si_rec), size_si_rec);
        }else{
            printf("%c is not a cmd. \n", cmd);
            continue ;
        }
    }
    close(s);
    return 0;
}