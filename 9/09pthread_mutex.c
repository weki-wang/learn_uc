// 该函数测试互斥锁，首先主线程读取用户的输入的数据，然后辅助线程等用户每输入一个数据，进行一次排序，最后将排序的结果输出到屏幕；
// 主要实现方式：主线程锁住数据，当读取到一个数据的时候，放开锁，然后辅助线程获取锁并排序然后放开锁
// 该程序存在一定问题，通过时间控制锁的抢占顺序。当辅助线程睡眠时间过短时，可能出现辅助线程运行2次，但主线程只运行一次
// 可通过信号量实现线程同步(见10semaphore程序)
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // 锁的声明和初始化

void * func(void * data_rec){
	int * d = data_rec;
	// 插入排序
	int j,k, temp_data ;
	for(j = 0 ; j < 10; j++){
		// 进行插入排序
		pthread_mutex_lock(&lock);
		printf("辅助线程接收到第%d个元素值为%d \n", j, d[j]);
		for(k = j; (k > 0) && (d[k] < d[k-1]); k--){			
			temp_data = d[k]; 
			d[k] = d[k-1];
			d[k-1] = temp_data;
		}

		// 显示结果
		printf("排序结果为:");
		for( k = 0; k < 10; k++){
			printf("%d ", d[k]);
		}
		printf("\n");
		pthread_mutex_unlock(&lock);
		usleep(500);
	}
	return (void *)0;
}


int main()
{
	// 数组的定义
	int data[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ;
	pthread_mutex_lock(&lock); 
	// 创建辅助线程
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, func, (void *)data);
	// 开始读取用户输入
	int i = 0;
	int num ;
	for (i = 0; i < 10; i++){
		printf("请输入第%d个整数：", i);
		fflush(stdout);
		scanf("%d", &num);
		data[i] = num;
		// 在对数组赋值完成后，解锁，然后等待1us,再加锁，这样可以让辅助线程可以获取锁
		pthread_mutex_unlock(&lock);
		usleep(50);
		pthread_mutex_lock(&lock); // 等待辅助线程的一次排序完成
	}
	// 处理完成，显示结果
	for(i = 0; i < 10; i++){
		printf("%d ", data[i]);
		fflush(stdout);
	}
	printf("\n");
	pthread_mutex_unlock(&lock);
	// 取消辅助线程并等待辅助线程结束
	pthread_cancel(thread_id);
	pthread_join(thread_id, NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}
