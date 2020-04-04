/* 该程序通过互斥量保护数据，通过信号量semaphore使多线程同步
 * 两个线程为:主线程读取用户的输入，辅助线程对输入的值进行排序，最后输出结果 
 *
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
static sem_t sem;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void * func(void *d){
	int * data = d;
	int j, k;
	for(j = 0; j < 10; j++){
		// 等待主线程的信号量,然后对数组进行插入排序
		sem_wait(&sem);
		pthread_mutex_lock(&lock);
		int value = data[j];
		for(k = j; k > 0 && value < data[k-1] ; k--){
			data[k] = data[k-1];
		}
		data[k] = value;
		pthread_mutex_unlock(&lock);
		usleep(1);
	}
	return (void *)0;
}

int main(void)
{
	int data[10];
	pthread_t thread_id;
	sem_init(&sem, 0, 0); // 初始化信号量为0
	pthread_create(&thread_id, NULL, func, (void *)data);
	// 主线程读取输入，辅助线程进行排序
	int i;
	for(i = 0; i < 10; i++){
		printf("请输入数组的%d个元素的值：", i+1);
		fflush(stdout);
		pthread_mutex_lock(&lock);
		scanf("%d", &data[i]);
		pthread_mutex_unlock(&lock);
		sem_post(&sem); // 信号量+1，即给辅助线程一个信号，让其进行排序工作
		usleep(1);
	}
	// 等待辅助线程计算完成
	pthread_join(thread_id, NULL);
	sem_destroy(&sem);
	pthread_mutex_destroy(&lock);
	// 显示排序结果
	for(i = 0; i < 10; i++){
		printf("%d ", data[i]);
		fflush(stdout);
	}
	printf("\n");
	return 0;
}
