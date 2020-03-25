#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void f1(void){puts("f1()");}
void f2(void){puts("f2()");}
void f3(int n, void *p){ 
    printf("n = 0x%x, p= %p \n", n ,p);
    free(p);
}
int main()
{
    // 只登记
    atexit(f1);
    atexit(f2);
    void *q = malloc(10);
    on_exit(f3,q);
    printf("groupid : %d \n", getpgid(getpid()));
    return 0;
    
}