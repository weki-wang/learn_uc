#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    puts("欢迎使用weki shell! 输入q退出");
    char cmd[256];
    char * temp_ptr = NULL;
    while(1){
        printf("weki shell $> ");
        scanf(" %[^\n]", cmd);//空白表示跳过空白字符直到遇到非空白字符为止
        if (cmd[0] == 'q' && cmd[1]== '\0')
            break;
        if (strncmp(cmd, "cd ", 3)==0)
            chdir(cmd+3);
        else if (temp_ptr = strchr(cmd,'=')){
            *temp_ptr = '\0';
            setenv(cmd, temp_ptr+1, 1);
        }
        else
            system(cmd);
    }
    printf("感谢使用weki shell，再见！\n");
    return 0;
}