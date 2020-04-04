// 该程序测试函数pthread_cancel 和pthread_exit两个函数
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void * func(void * d){
    while(1){
        printf("你好.");
        fflush(stdout);
        sleep(1);
    }
}

int main()
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, func, NULL);
    sleep(5);
    // 终止辅助线程
    pthread_cancel(thread_id);
    pthread_join(thread_id, NULL);
    // 终止本线程
    pthread_exit(NULL);
}
