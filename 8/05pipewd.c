//该文件与06piperd配合主要测试命名管道，该文件主要是写，06是读
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
    mkfifo("pipe", 0644); // 创建命名管道
    int fd = open("pipe",O_WRONLY);
    if(fd==-1){
        printf("error:[%m] \n");
        return -1;
    }
    puts("打开管道成功！");
    puts("请输入姓名、年龄、体重： \n");
    PersonInfo p;
    scanf("%s%d%lf", p.name, &p.age, &p.weight);
    write(fd, &p, sizeof(p));
    close(fd); // 关闭管道
}