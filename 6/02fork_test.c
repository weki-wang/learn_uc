#include <stdio.h>
#include <unistd.h>
int main()
{
    if(fork() == 0){
        puts("1");
    }
    if(fork()!= 0){
        puts("2");
    }
    puts("3");
}