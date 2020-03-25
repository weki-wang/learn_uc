#include <stdio.h>
#include <dlfcn.h>

int main(void)
{
	int n;
	void *handle = NULL;
	puts("请输入选项：1-中文，2：English\n");
	scanf("%d",&n);
	if (n ==1)
		handle = dlopen("libmych.so",RTLD_NOW);
	else if (n ==2)
		handle = dlopen("libmyen.so",RTLD_NOW);
	else
		puts("输入的参数错误！");
	/*检查是否错误 */
	char * error = NULL;
	error = dlerror();
	if (error != NULL ){
		printf("%s",error);
		return -1;
	}
	/* 获取显示函数的地址 */
	void (*fp)(void);
	fp = dlsym(handle,"display");
	/*检查是否错误 */
	error = dlerror();
	if (error != NULL ){
		printf("%s",error);
		return -1;
	}
	/* 显示 */
	fp();
	dlclose(handle);
	return 1;
}
