/* 该程序用于检测大小端的问题,同时测试字节转换函数 */

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef union data{
	char ch[4];
	int num;
}data_union;

int main(void)
{
	data_union temp;
	temp.num = 0x11223344;
	if(temp.ch[0] == 0x11)
		puts("该系统为大端储存");
	else if(temp.ch[0] == 0x44)
		puts("该系统为小端储存");
	else
		puts("程序错误，检测失败");
	
	/*进行字节转化后，显示储存方式 */
	temp.num = htonl(temp.num); 
	if(temp.ch[0] == 0x11)
		puts("转化后数据为大端储存");
	else if(temp.ch[0] == 0x44)
		puts("转化后数据为小端储存");
	else
		puts("转化错误");
	
	return 0;
}

