#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
int main(int argc, char *argv[])
{
	if (argc < 2){
		puts("缺少参数，请加上一个目录名或文件名！");
		return -1;
	}
	struct stat buf;
	lstat(argv[1], &buf);
	printf("该文件的信息为：\n");
	printf("文件ID:%ld, 用户名%s, 总字节数%ld\n",buf.st_ino,
	(getpwuid(buf.st_uid))->pw_name, buf.st_size);
	struct tm *ap = localtime(&(buf.st_atim.tv_sec));
	struct tm *mp = localtime(&(buf.st_atim.tv_sec));

	//localtime_r(&(buf.st_atim.tv_sec), ap);
	//localtime_r(&(buf.st_mtim.tv_sec), mp);
 	printf("文件最后访问的时间为：%d年%d月%d日%02d时%02d分%02d秒\n",
	ap->tm_year + 1900, ap->tm_mon + 1, ap->tm_mday, ap->tm_hour, ap->tm_min, ap->tm_sec);
	printf("文件最后修改的时间为：%d年%d月%d日%02d时%02d分%02d秒\n",
	mp->tm_year + 1900, mp->tm_mon + 1, mp->tm_mday, mp->tm_hour, mp->tm_min, mp->tm_sec);
	return 0;
}
