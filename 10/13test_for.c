#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
    while(1){
        int i;
        puts("不正常:");
        // 注意，for的判断语句是打破for循环的，而和if的选择性执行不一样
        for(i = 0;((i<20)&&(i%2 == 0));i++){
            printf("%d ",i);
        }
        printf("\n");
        printf("正常: \n");
        for(i= 0; ;i++){
            if((i%2==0)&&(i<20))
                printf("%d ",i);
            else if(i>=20)
                break;
        }
        printf("\n\n");
        sleep(1);
    }
    return 0;
}