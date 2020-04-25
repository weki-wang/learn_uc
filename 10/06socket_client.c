/*该程序测试SOCKET网络通信其中的服务器
 * 
 *
*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("%s IP PORT. \n", argv[0]);
        exit(-1) ;
    }
    // 创建客户端
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket failed");
        exit(-1) ;
    }
    // 连接服务器
    struct sockaddr_in si;
    si.sin_family = AF_INET;
    if(inet_aton(argv[1], &(si.sin_addr)) == 0){
        printf("Invalid  IP address \n");
        exit(-1) ;
    }
    si.sin_port = htons(atoi(argv[2])); // 必须使用htons
    if( connect(fd, (struct sockaddr *)(&si), sizeof(si)) < 0 ){
        perror("connect failed");
        exit(-1) ;
    }else{
        printf("服务器连接成功... \n");
    }
    // 不断收发数据
    char msg[1024];
    while(1){
        printf("输入：");
        fflush(stdout);
        scanf(" %[^\n]", msg);

        if(msg[0] == 'q')
            break;
        write(fd, msg, strlen(msg));
        int n = read(fd, msg, sizeof(msg) - 1 );
        if(n<= 0){
            break;
        }
        msg[n] = '\0';
        printf("服务器的回应为: %s \n", msg);
    }
    puts("关闭客户端...");
    close(fd);
    return 0;
}
