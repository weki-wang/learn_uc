/*该程序测试SOCKET网络通信其中的服务器
 * 
 *
*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>  /* gethostbyname */
#include <sys/types.h>
#include <pthread.h>

#define PORT 8890
typedef struct Param{
	char *ip_;
	int fd_;
}Param;

void * func(void *p){
	// 读取客户端发送的数据
	Param * p_data = (Param *)p;
	char msg[1024];
	char temp_msg[1024];
	while(1){
		int n = read(p_data->fd_, msg, sizeof(msg)-1);
		if(n <= 0)
			break;
		if(msg[0] == 'q') break;
		msg[n] = '\0';
		sprintf(temp_msg, "IP为%s的用户，您发送的是:", p_data->ip_);
		write(p_data->fd_, temp_msg, strlen(temp_msg));
		write(p_data->fd_, msg, strlen(msg));
		printf("服务器接受到%s的用户的数据：%s.", p_data->ip_, msg);
		fflush(stdout);
	}
	// 当关闭了输入时退出
	close(p_data->fd_);
	printf("退出对IP为%s的服务. \n", p_data->ip_);
	free(p);
	return (void *)0;
}

int getLocalIp(in_addr_t *ip){
	char hostname[128];
	int ret = gethostname(hostname, sizeof(hostname));
	if(ret == -1){
		perror("gethostname");
		return -1;
	}
	printf("本机名为:%s \n", hostname);
	struct hostent *hent;
	hent = gethostbyname(hostname);
	if(hent == NULL){
		herror("gethostbyname");// 不能使用perror 因为gethostbyname没有使用errno，而是设置了h_errno
		return -1;		
	}
	*ip = ( ((struct in_addr *)hent->h_addr_list[0])->s_addr);  // 注意，此时已经是网络字节顺序，不需要再转换
	/*
	char ip_p[16];
	// 查看所有IP
	int i,j;
	unsigned char *num;
	for(i = 0; hent->h_addr_list[i] != NULL ; i++){

		*ip = ( ((struct in_addr *)hent->h_addr_list[i])->s_addr); 
		num = (unsigned char *)ip;
		for(j = 0; j < 4; j++){
			printf("%d ",*num++);
		}
		printf("\n");
		inet_ntop(AF_INET, &ip, ip_p, sizeof(ip_p));
		printf("使用inet_ntop本地IP为: %s \n",ip_p); // 该方法存在问题，因为本地大小端储存顺序和网络字节顺序不一致 
		printf("使用inet_ntoa本地IP为: %s \n",inet_ntoa(*((struct in_addr *)ip)));	// 建议使用该方法  	
	}
	*/
	return 0;
}

int main(void)
{
	// 创建一个IPv4的socket套接字(即首先创建一个话机)
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0){
		perror("socket failed");
		return -1;
	}
	// 绑定一个IP和端口(即话机绑定电话号)
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	// 获取本机IP，注意该地方必须使用网络字节顺序(大端)
	if(getLocalIp(&si.sin_addr.s_addr ) == -1){
		printf("in %s file, line %d getLocalIp failed. \n", __FILE__, __LINE__);
		return -1;
	}
	/*
	si.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, "192.168.0.107", &si.sin_addr.s_addr);
	*/
	si.sin_port = htons(PORT); /* 端口号,禁止直接使用port而不用htons转换，因为字节储存顺序可能不一致 */ 
	printf("服务器的IP为:%s, 端口号为%d \n", inet_ntoa(si.sin_addr), PORT);
	if (bind(fd, (struct sockaddr *)&si, sizeof(si)) < 0){
		perror("bind failed");
		return -1;
	}
	// 支持多路
	listen(fd, 10); // 允许同时10个接入请求
	puts("服务器初始化完成，等待客户端的接入请求...");
	while(1){
		struct sockaddr_in sic;
		socklen_t len = sizeof(sic); // 必须初始化成本地套接信息长度
		int fd_c = accept(fd, (struct sockaddr *)&sic, &len); // 等待客户连接，返回一个跟客户相连接的新套接字
		if(fd_c < 0){
			sleep(1);
			continue;
		}
		char ip[16]; // IPv4
		inet_ntop(AF_INET, &sic.sin_addr, ip, sizeof(ip));
		printf("接受到IP为%s的接入请求,此时的fd_c为%d\n", ip, fd_c);
		// 开启一个线程
		Param *p_param = malloc(sizeof(Param));
		p_param->ip_ = ip;
		p_param->fd_ = fd_c;
		pthread_t thread_id;
		pthread_create(&thread_id, NULL, func, (void *)p_param);

	}
}



