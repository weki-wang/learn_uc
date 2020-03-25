#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open("get_lock_log.txt", O_RDWR|O_CREAT, 0777);
    if (fd == -1){
        perror("open failed : ");
        return -1;
    }
    struct flock pos;
    pos.l_type = F_WRLCK;
    pos.l_whence = SEEK_SET; // 开始的位置
	pos.l_start = 19; // 从离文件头19个字节开始
	pos.l_len = 17; // 枷锁长度17个字节
    if(fcntl(fd, F_GETLK, &pos) == -1){
        perror("getlock");
        return -1;
    }
    if (pos.l_type == F_UNLCK) puts("未被加锁");
    else{
        puts("文件已被加锁：");
        printf("进程id：%d \n", pos.l_pid);
        printf("锁类型：%s \n", pos.l_type == F_RDLCK ? "读锁" : pos.l_type == F_WRLCK ? "写锁" : "未加锁");
    }
    close(fd);
    return 0;
    

}