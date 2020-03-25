#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    umask(0);
    int fd = open("mmap.txt",O_RDWR);
    if (fd == -1){
        perror("open failed : ");
        return -1;
    }
    char *p = mmap(0,1024,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap failed : ");
        return -1;
    }
    int count = 0;
    while(1){
        if(p[0]!='\0'){
            printf("%s",p);
            memset(p, 0, strlen(p));
            count = 0;
        }else{
            if (++count > 20)
                break;
        }
        usleep(1000*500);
    }
    munmap(p,1024); // 解除映射
    close(fd);
    puts("ending...");
    return 0;
}