#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main ()
{
    // 打开文件
    int fd = open("process_id", O_RDONLY);
    pid_t id;
    //读取需要杀死的进程id
    char cmd[256];
    while((read(fd, &id, sizeof(id))) == sizeof(id)){
        sprintf(cmd, "kill %d", id);
        system(cmd);
    }
    // 关闭文件
    close(fd);
    // 删除文件
    unlink("process_id");
    return 0;
}