#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    umask(0);
    int fd = open("mmap.txt",O_RDWR|O_CREAT, 0777);
    if (fd == -1){
        perror("open failed : ");
        return -1;
    }
    ftruncate(fd, 1024); // 把文件截成1k长
    char *p = mmap(0,1024,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap failed : ");
        return -1;
    }
    while(1){
        int n = read(STDIN_FILENO, p, 1024);
        if (n <= 0) break;
    }
    munmap(p,1024); // 解除映射
    close(fd);
}