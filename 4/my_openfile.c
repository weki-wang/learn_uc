#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main (int argc, char* argv[])
{
	int fd = open("log.txt",O_RDWR|O_CREAT,0777);
	if(fd < 0){
		perror("Open failed : ");
		return -1;
	}
	unsigned int id = '1';
	read(fd, &id, sizeof(id));
	++id;
	write(fd, &id, sizeof(id));
	close(fd);
	printf("id=%u \n", id);
	return 0;
}
