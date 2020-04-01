#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // 获取id
    int id = shmget(0x8888, 100, 0);
    // 挂载共享内存
    char *p = shmat(id, NULL, SHM_RDONLY);
    if ( p == (char *)-1){
        perror("shmat failed:");
        return -1;
    }
    // 打印内容
    puts(p);
    // 解除挂载
    shmdt(p);
    // 删除共享内存
    shmctl(id, IPC_RMID, NULL);
    return 0;
}