#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
int main(int argc, char *argv[])
{
    struct winsize w;
    for(;;){
        ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
        printf("col is %d, and row is %d", w.ws_col, w.ws_row);
        usleep(1000000);
    }
    return 0;
}