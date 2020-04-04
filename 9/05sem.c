// 05 测试信号量的文件，主要功能是限制只有5个进程同时在工作
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    // 创建一个信号量集，该信号量集中信号量为1个
    int id = semget(0x8888, 1, IPC_CREAT|0600);
    if(id == -1){
        perror("semget failed:");
        return -1;
    }
    // 设置信号量集的值为5
    semctl(id, 0, SETVAL, 5);
    int i;
    for(i = 0; i < 10; i++){
        if(fork()==0){
            // 子进程
            // 首先每个子进程对信号量进行操作-1，如果失败阻塞
            struct sembuf sb;
            sb.sem_flg = SEM_UNDO;
            sb.sem_num = 0;
            sb.sem_op = -1;
            while(semop(id, &sb, 1) == -1){;} // 在这里如果操作失败，则堵塞
            srand(getpid());
            printf("%d进程开始工作\n", getpid());
            sleep(rand()%15+5);
            printf("%d进程结束工作\n", getpid());
            // 结束后复原信号量，如果直接结束也可以，因为SEM_UNDO参数会使系统会帮忙复原
            sb.sem_op = 1;
            semop(id, &sb, 1);
            exit(3);
        }
    }
    // 等待进程工作完毕，回收进程资源
    int statu;
    pid_t pid;
    for(i = 0; i < 10; i++){
        pid = waitpid(-1, &statu, 0);
        if(pid == -1){
            perror("waitpaid failed:");
            return -1;
        }
        // 显示被回收的进程号，和返回值
        printf("进程%d的资源已被回收，其返回值为%d\n",pid, WEXITSTATUS(statu));
    }

    // 删除该信号量集
    puts("所有进程已结束，且进程资源已被回收");
    semctl(id, 0, IPC_RMID, NULL);
    return 0;

} 