#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
// 获取文件类型
void PrintfFileType(mode_t st_mode){
	if( S_ISREG(st_mode))	putchar('-'); // 普通文件
	else if(S_ISDIR(st_mode)) putchar('d'); // 目录文件
	else if(S_ISLNK(st_mode)) putchar('l'); // 链接文件
	else if(S_ISCHR(st_mode)) putchar('c'); // 字符设备
	else if(S_ISFIFO(st_mode)) putchar('p'); // 管道
	else if(S_ISSOCK(st_mode)) putchar('s'); // 网络套接字
	else if(S_ISBLK(st_mode)) putchar('b'); // 块设备
	else putchar('@'); // 其他
};
// 获取并打印权限
void PrintfFileAccess(mode_t st_mode){
	const char s[] = "rwx";
	int i = 0;
	for(;i<9;i++, st_mode <<= 1) 
		st_mode & 0400 ? putchar(s[i%3]) : putchar('-');
	putchar(' ');
};
// 获取文件的硬链接数目
PrintfFileINodeUseNum(nlink_t st_nlink){
	printf("%2d ", st_nlink);
};
// 获取文件所有者
PrintfFileUseName(uid_t st_uid){
	struct passwd *p = NULL;
	if(p = getpwuid(st_uid))
		printf("%s ", p->pw_name);
};
// 获取文件所有者对应的组别
PrintfFileUseGrapha(gid_t st_gid){
	struct group *p = NULL;
	if(p=getgrgid(st_gid))
		printf("%s ", p->gr_name);
}; 
// 获取文件大小
PrintfFileSizeData(off_t st_size){
	printf("%5ld ", st_size);
};
// 获取访问时间
PrintfFileAccessTime(struct timespec st_atim){
	struct tm *tim_ptr = NULL;
	if( tim_ptr = localtime(&(st_atim.tv_sec)))
		printf("%2d月 %2d %2d:%2d ", tim_ptr->tm_mon + 1, tim_ptr->tm_mday, tim_ptr->tm_hour, tim_ptr->tm_min);
};
// 获取文件名
PrintfFileName(char *name){
	printf("%s \n", name);
}; 

int main(int argc, char *argv[])
{
	DIR * current_dir_ptr = opendir(".");
	struct dirent *dir_ptr = NULL;
	struct stat s ;
	while((dir_ptr = readdir(current_dir_ptr))!=NULL){
		lstat(dir_ptr->d_name, &s); // 获取详细信息
		PrintfFileType(s.st_mode); // 获取文件类型
		PrintfFileAccess(s.st_mode); // 获取并打印权限
		PrintfFileINodeUseNum(s.st_nlink); // 获取文件的硬链接数目
		PrintfFileUseName(s.st_uid); // 获取文件所有者
		PrintfFileUseGrapha(s.st_gid); // 获取文件所有者对应的组别
		PrintfFileSizeData(s.st_size); // 获取文件大小
		PrintfFileAccessTime(s.st_atim); // 获取文件最近的访问访问时间
		PrintfFileName(dir_ptr->d_name); // 获取文件名
	}
	closedir(current_dir_ptr);
	return 0;
}
