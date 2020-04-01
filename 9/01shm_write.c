// 测试共享内存(shared memory)的程序
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
int main()
{
    // 创建一个共享内存
    int id = shmget(0x8888, 100, IPC_CREAT|0644);
    printf("创建的共享内存id为%d \n", id);
    // 挂载到本地
    char *p = shmat(id, NULL, 0);
    if ( p == (char *)-1){
        perror("shmat failed:");
        return -1;
    }
    // 写数据
    char str[] = "uc 真好玩 \n";
    strncpy(p, str, sizeof(str));
    // 解除挂载
    shmdt(p);

    return 0;
}