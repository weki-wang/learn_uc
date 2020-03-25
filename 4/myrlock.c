#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	int fd = open("get_lock_log.txt",O_RDWR|O_CREAT, 0777);
	if(fd == -1){
		perror("open failed : ");
		return -1;
	}
	struct flock pos;
	pos.l_type = F_RDLCK; // 读锁
	pos.l_whence = SEEK_SET; // 开始的位置
	pos.l_start = 19; // 从离文件头19个字节开始
	pos.l_len = 17; // 枷锁长度17个字节
	int r = fcntl(fd, F_SETLK, &pos);
	if(r == -1){
		perror("加读锁失败： ");
		return -1;
	}
	puts("加读锁成功！");
	sleep(20);
	pos.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &pos);
	puts("解锁完毕");
	return 0;
	
}
