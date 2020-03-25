#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    int fd[3];
    char ch[3] = {'a', 'b', 'c'};
    char * str[] = {"is_close_a", "is_close_b", "is_close_c"};
    pid_t id;
    // 打开文件 -- 储存子进程(孤儿进程)的id
    umask(0);
    int fd_id = open("process_id_file.txt", O_RDWR|O_TRUNC|O_CREAT, 0666);
    if( fd_id == -1){
        perror("open failed : ");
        return -1;
    }
    // 创建进程
    for(int i = 0; i < 3; i++){
        if((id = fork())==0){
            while(1){
                printf("%c \n",ch[i]);
                // 如果打开某个文件成功，则表示子进程需要结束
                if((fd[i] = open(str[i],O_RDONLY)) != -1){
                    close(fd[i]);
                    unlink(str[i]); // 删除文件
                    break;
                }
                sleep(1);
            }
            int exit_num = 88 + i;
            printf("读取文件%s成功，子进程%d退出, 返回值为%d \n", str[i], getpid(), exit_num);
            exit(exit_num);
        }else{
            printf("第%d次创建进程, 本进程是%d, 创建的子进程是%d \n", i, getpid(), id);
            char buf[256];
            sprintf(buf, "%d", id);
            // 将子进程的id写入文档中
            write(fd_id, buf, sizeof(buf));
            // 添加回车
            write(fd_id, "\n", 1);
        }
    }
    printf("创建进程结束， 父进程自动结束！ \n");
    close(fd_id);
    exit(2);
}