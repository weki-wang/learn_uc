// 多线程测试程序，注意要连接pthread静态库
// 该程序主要实现为：辅助线程在一个20个元素里面每秒放一个整数，从100开始，依次递增，顺序放在数组里面，主线程每秒从该数组里面读取一个元素显示
// 同时添加一个新的辅助线程，检测用户是否停止程序， 注意，暂时不知道是否会产生死锁
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
static pthread_mutex_t lock; // 互斥锁
// 定义程序结束标志,1表示程序结束，通过ctrl+c产生，0表示继续
int is_stop = 0;
const int size = 20; // 数组大小
// 信号处理函数
void SignalHandle(int sig){
    if(sig ==SIGINT){
        printf("接收到 SIGINT 信号. \n");
        pthread_mutex_lock(&lock);
        is_stop = 1; // 让程序停止
        pthread_mutex_unlock(&lock);
        printf("正在向所有线程发送停止信号... \n");
    } 
}
// 辅助线程0的主函数-填充data里面的数据
void *set_data(void * d){
    int i = 0;
    int num = 100;
    while(1){
        // 加锁,数组赋值后解锁
        // printf("辅助线程0正在获取锁... \n");
        pthread_mutex_lock(&lock);
        if(is_stop == 1){
            printf("辅助线程0已经接收到停止信号，正在停止... \n");
            break;
        }
        *((int *)d + i) = num;
        printf("正在为data数组里第%d个元素赋值为%d... \n", i, num);
        pthread_mutex_unlock(&lock);
        // printf("辅助线程0正在释放锁... \n");
        if(++i >= size) i = 0;
        if(++num >= 200) num = 100;
        sleep(1);
    }
    printf("辅助线程0已经停止. \n");
}
// 辅助线程1的主函数-检测是否需要停止主程序
void *DetectStop(void * stop_flag){
    // 登记信号处理函数
    printf("辅助线程1登记信号处理函数中... \n");
    signal(SIGINT, SignalHandle);
    printf("辅助线程1登记完成，已结束. \n");
}
int main()
{
    // 定义数组
    int data[size];
    // 初始化互斥锁
    if( pthread_mutex_init(&lock, NULL) != 0){
        perror("pthread_mutex_init failed:");
        return -1;
    }
    pthread_t thread_id[2];
    // 创建一个新的辅助线程,该线程主要是对组数进行填充操作
    pthread_create(&thread_id[0], NULL, set_data, (void *)data);
    // 创建一个新的辅助线程，主要是检测程序是否该结束
    pthread_create(&thread_id[1], NULL, DetectStop, NULL);
    // 主函数循环读取参数里面的值
    int i = 0;
    sleep(2);
    while(1){
        // printf("主线程正在获取锁... \n");
        pthread_mutex_lock(&lock);
        if(is_stop == 1){
            printf("主线程收到停止信号,正在等待辅助线程结束... \n");
            pthread_mutex_unlock(&lock);
            break;
        }
        // 读取数组里面的数组并显示
        printf("数组data里面的第%d个元素的值为%d. \n", i, data[i]);
        if(++i >= size) i = 0;
        pthread_mutex_unlock(&lock);
        // printf("主线程正在释放锁... \n");
        sleep(1);
    }
    // 等待辅助线程的结束
    printf("等待辅助线程0结束... \n");
    pthread_join(thread_id[0], NULL);
    printf("辅助线程0已结束. \n");
    printf("等待辅助线程1结束... \n");
    pthread_join(thread_id[1], NULL);
    printf("辅助线程1已结束. \n");
    // 注销互斥锁
    pthread_mutex_destroy(&lock);
    printf("主线程已结束. \n");
}