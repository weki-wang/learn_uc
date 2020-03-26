//该文件与05pipewd配合主要测试命名管道，该文件主要是读，06是读
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Person {
    char name[20]; // 不能使用指针,因为虚拟内存
    int age;
    double weight;
} PersonInfo;

int main()
{
    int fd = open("pipe", O_RDONLY);
    if(fd == -1){
        perror("open pipe failed");
        return -1;
    }
    puts("打开管道成功");
    PersonInfo p;
    if( (read(fd, &p, sizeof(p))) != sizeof(p) ){
        perror("read error");
        return -1;
    }
    printf("姓名： %s , 年龄： %d岁, 体重： %lf kg \n", p.name, p.age, p.weight);
    close(fd);
}