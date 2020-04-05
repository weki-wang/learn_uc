// 该程序用于测试pthread_cond的条件变量，注意pthread_cond 与 pthread_mutex必须一起使用
// 主线程获取用户的输入，确定输出的内容，辅助线程根据主线程的输入按一定频率输出字符串
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static pthread_mutex_t thread_lock;
static pthread_cond_t thread_cond;
static int flag = 0;

void *func(void * data){
	while(1){
		pthread_mutex_lock(&thread_lock);
		// 根据flag判断线程的执行
		if(flag == 0){
			pthread_cond_wait(&thread_cond, &thread_lock); // 先解锁，然后等待条件变量，当收到条件变量时，加锁，然后结束wait
			pthread_mutex_unlock(&thread_lock);

		}
		else if(flag == 3){
			pthread_mutex_unlock(&thread_lock);
			break;
		}else{
			pthread_mutex_unlock(&thread_lock);
			printf("%c",*((char *)data));
			fflush(stdout);
		}
		sleep(1);
	}
	return (void *)0;
}

int main(void)
{
	pthread_t thread_id[2];
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_cond, NULL);
	// 创建辅助线程	
	pthread_create(&thread_id[0], NULL, func, "*");
	pthread_create(&thread_id[1], NULL, func, ".");
	// 读取用户输入
	printf("请输入字符(q退出，a输出某一个字符，b输出全部字符，x关闭输出)：");
	fflush(stdout);
	char temp_ch;
	while(1){
		scanf(" %c",&temp_ch);
		pthread_mutex_lock(&thread_lock);
		if(temp_ch == 'q'){
			flag = 3;
			pthread_cond_broadcast(&thread_cond); // 通知所有线程关闭
			pthread_mutex_unlock(&thread_lock);
			break;
		}else if(temp_ch == 'a'){
			flag = 1;
			pthread_cond_signal(&thread_cond); // 任意通知一个辅助线程开启打印
		}else if(temp_ch == 'b'){
			flag = 1;
			pthread_cond_broadcast(&thread_cond); // 通知所有辅助线程开启打印
		}else if(temp_ch == 'x') {
			flag = 0;
		}
		pthread_mutex_unlock(&thread_lock);
		sleep(1);
	}
	// 退出程序
	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
	pthread_mutex_destroy(&thread_lock);
	pthread_cond_destroy(&thread_cond);
	return 0;
}
