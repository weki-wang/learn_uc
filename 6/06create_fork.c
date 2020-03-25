#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main ()
{
    pid_t pid;
    // 创建进程
    for(int i = 0; i < 3; i++){
        // 子进程进行循环打印
        if((pid = fork()) == 0){
            char c = 'a' + i;
            while(1){
                write(STDIN_FILENO, &c, sizeof(c));
                sleep(1);
            }
        }else{
            // 父进程将子进程的id的储存在文件中
            int fd = open("process_id", O_WRONLY|O_CREAT|O_APPEND, 0644);
            // 储存进程id
            write(fd, &pid, sizeof(pid));
            // 关闭文件
            close(fd);
        }
    }
    printf("进程创建完成！ \n");
    return 0;
}