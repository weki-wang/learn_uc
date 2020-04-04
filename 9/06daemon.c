// 写的一个守护进程(精灵进程)，在后台运行
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/types.h>
int main()
{
    // 把进程设置为服务(精灵)进程
    daemon(0,0);
    // 获取用户名和其主目录，然后修改当前目录至用户的主目录
    chdir(getpwuid(getuid())->pw_dir);
    char c = 'z';
    const char n = '\n';
    while(1){
        int fd = open("letter", O_RDWR|O_CREAT, 0644);
        read(fd, &c, 1);
        if(++c > 'z')
            c = 'a';
        lseek(fd, 0, SEEK_SET);
        write(fd, &c, 1);
        write(fd, &n, 1);
        close(fd);
        sleep(1);
    }
}