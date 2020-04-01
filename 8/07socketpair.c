/* 匿名本地网络通讯(网络套接字)的测试程序 */
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
int main()
{
    int s[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, s);
    int char_num;
    char buf[100];
    if(fork()== 0){
        // 子进程，将字符交换顺序
        while( (char_num = read(s[0], buf, sizeof(buf)))>0 ){
            // 交换顺序
            if(buf[0] == 'q') break;
            int i;
            --char_num;
            for(i = 0; i< char_num/2; i++){
                char c = buf[i];
                buf[i] = buf[char_num-1-i];
                buf[char_num-1-i] = c;
            }
            write(s[0], buf, char_num+1);
        }
        close(s[0]);
    }
    else{
        // 父进程读取键盘的输入，然后接受子进程转化后的字符串
        while(1){
            // 读取键盘的输入
            char_num = read(STDIN_FILENO, buf, sizeof(buf));
            // 通过套接字发给子进程
            write(s[1], buf, char_num);
            if(buf[0] == 'q') break;
            // 从套接字接受字符
            char_num = read(s[1], buf, sizeof(buf));
            // 在屏幕上显示
            write(STDOUT_FILENO, buf, char_num);
        }
        close(s[1]);
        waitpid(0, NULL, 0); // 回收子进程资源
        puts("已回收子进程资源");
        return 0;
    }
}