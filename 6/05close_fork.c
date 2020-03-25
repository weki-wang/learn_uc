#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    // 打开进程id的文件
    int id[3];
    FILE* fd_id = fopen("process_id_file.txt", "r");
    if(fd_id == NULL){
        printf("error srting:[%m] \n");
        return -1;
    }
    char str_id[256];
    for(int i = 0; i < 3; i++){
        //读取三个孤儿id
        fscanf(fd_id, " %[^\n]", str_id);
        id[i] = atoi(str_id);
        printf("读取的进程id为%d \n",id[i]);
    }
    // 关闭进程id文件
    fclose(fd_id);
    // 创建文件以关闭进程
    int fd1 = open("is_close_a", O_RDWR|O_CREAT, 0777);
    if(fd1 < -1){
        perror("open failed: ");
        return -1;
    }
    int fd2 = open("is_close_b", O_RDWR|O_CREAT, 0777);
    if(fd2 < -1){
        perror("open failed: ");
        return -1;
    }
    int fd3 = open("is_close_c", O_RDWR|O_CREAT, 0777);
    if(fd3 < -1){
        perror("open failed: ");
        return -1;
    }
    close(fd1);
    close(fd2);
    close(fd3);
    // 回收进程资源,并判断进程结束的状态
    int s[3];
    for(int i = 0; i < 3 ; i++)
        waitpid(id[i], &s[i], 0);
    for(int i = 0; i < 3; i++){
        if(WIFEXITED(s[i])){
            printf("进程%d是正常结束的,返回值为%d \n", id[i], WEXITSTATUS(s[i]));
        }else{
            printf("进程%d是被信号终止的 \n", id[i]);
        }
    }
    return 0;
}