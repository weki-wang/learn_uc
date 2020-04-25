/* 本程序主要比较const 指针和 const 引用之间的顺序的区别 */

#include <iostream>
#include <stdio.h>


int main(void)
{
    int a = 10;
    const int b = 10;
    // int const a = 10;  //此语句和上一个语句一样，表示一个常量int

    /* 指向const地址的指针，该指针可以改变指向其他地方 */

    const int *c = &a;  // const 修饰int，即指针c指向位置的值不能被改变，但指针c指向的位置可以改变
    c = &b; // right， 可以改变指针c指向的地址
    // *c = 20 ; // error, 不能改变指针c指向地址的值
    int const *d = &b; // 此语句和const int *c表达的含义一样

    /* const 类型的指针，即该指针不能改变其指向的地址 */
    int * const e = &a; // const 修饰的是int类型的指针e，即指针e为const，而指针e指向地址的值可以被改变
    *e = 30; // right, 可以改变指针e指向地址的值
    // e = &b; // error, 不能改变指针指向的地址

    /*指针、引用*/
    int h = 10;
    int &i =h;
    const int * const k = &h; // 此处声明一个const指针k，它指向一个const整数
    const int * const &j = k; // 此处声明的是一个const指针(指向const整数)的引用j，即该j的储存地址和k是一样的只不过名称不一样

    /*
    printf("h addr is %p \n", &h);
    printf("j addr is %p \n", &j);
    printf("j ptr to addr is %p \n", j);
    printf("k addr is %p \n", &k);
    printf("k ptr to addr is %p \n", k);
    printf("j value is %d \n", *j);
    */
}