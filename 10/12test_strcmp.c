#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    char temp[1024];
    int n = read(STDIN_FILENO, temp, sizeof(temp)-1);
    int i;
    for(i = 0; temp[i] != '\0'; i++){
        printf("%d ", temp[i]);
    }
    printf("\n");
    char cs[] = "quit\n";
    for (i = 0; cs[i] != '\0'; i++)
        printf("%d ", cs[i]);
    printf("\n");   
    int x = strncmp(temp, cs, n);
    printf("%d \n", x);
    return 0;
}