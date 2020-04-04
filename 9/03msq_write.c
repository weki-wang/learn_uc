// 03 和 04 用于测试消息队列的使用
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct msg{
    long msg_type;
    char name[50];
    double socre;
    int age;
}msg;

int main()
{
    // 创建一个消息队列对象
    int id = msgget(0x1234, IPC_CREAT|0644);
    if(id == -1){
        perror("creat message queue failed:");
        return -1;
    }else
    {
        printf("创建消息队列成功，id为%d \n", id);

    }
    // 获取用户输入的参数
    msg m;
    puts("请输入消息类型，姓名，分数， 年龄：");
    scanf("%ld%s%lf%d", &m.msg_type, m.name, &m.socre, &m.age);
    // 向队列发送消息数据
    msgsnd(id, &m, sizeof(m), 0);
    return 0;
}