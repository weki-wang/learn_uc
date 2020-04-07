/* 该程序将字符串ip转化为内部ip，注意内部ip是以网络字节顺序(大端)储存的 */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(void)
{
	in_addr_t nip;
	char pip[16];
	inet_pton(AF_INET, "192.168.10.20", &nip);
	inet_ntop(AF_INET, &nip, pip, sizeof(pip));
	int i;
	unsigned char *p = (unsigned char *)&nip; 
	for(i = 0; i < 4; i++)
		printf("%d ",*p++);
	printf("\n");
	puts(pip);
	return 0;
}
