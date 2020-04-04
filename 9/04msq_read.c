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
    // 读取消息队列对象id
    int id = msgget(0x1234, 0);
    if (id == -1){
        perror("get message queue failed:");
        return -1;
    }else{
        printf("获取id为%d的对象成功 \n",id);
    }

    // 按照消息类型读取消息
    long type;
    msg rcv_msg;
    puts("请输入想要读取的消息的类型：");
    scanf("%ld", &type);
    int rcv_data_size = msgrcv(id, &rcv_msg, sizeof(rcv_msg), type, IPC_NOWAIT); // 必须是IPC_NOWAIT，否则0参数会使得获取失败会发生阻塞
    if(rcv_data_size == -1)
        printf("没有消息类型为%ld的消息. \n", type);
    else
        printf("消息类型：%ld\n姓名：%s\n年龄：%d\n分数：%lf\n", rcv_msg.msg_type, rcv_msg.name, rcv_msg.age, rcv_msg.socre);

    msgctl(id, IPC_RMID, NULL);
    return 0;       
}