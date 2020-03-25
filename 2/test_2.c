#include <stdio.h>

void f1()__attribute__((constructor));
void f2()__attribute__((destructor));
int main(void){
	puts("这里是主函数");
	return 0;
}

void f1(){puts("在main之前");}
void f2(){puts("在main之后");}
