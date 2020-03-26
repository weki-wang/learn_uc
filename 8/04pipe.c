#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <wait.h>
int main()
{
    int fd[2];
    pipe(fd);
    char buf[100];
    if(fork() == 0){
        // 子进程只读
        close(fd[1]); // 关闭写端
        int n;
        while( (n = read(fd[0], buf, sizeof(buf))) > 0 ){
            int i;
            for(i = 0; i < n; i++){
                if(islower(buf[i]))
                    putchar(toupper(buf[i]));
                else if(isupper(buf[i]))
                    putchar(tolower(buf[i]));
            }
        }
        close(fd[0]); // 读取结束后，关闭读端
    }
    else{
        // 父进程只写
        close(fd[0]); // 关闭读端
        while(1){
            int n = read(STDIN_FILENO, buf, sizeof(buf));
            if(buf[0] == 'q')
                break;
                write(fd[1], buf, n);
        }
        close(fd[1]); // 关闭写端
        waitpid(0,NULL, 0); // 回收子进程资源
    }
}