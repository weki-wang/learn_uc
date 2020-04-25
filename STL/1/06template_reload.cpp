/*本程序主要测试模板函数重载、模板函数特例化的知识 */
#include <iostream>
using namespace std;

/*模板函数 */
template <typename T>
void print(T  &d){
    cout << d << ' ';
}

/* 模板函数：上一个函数的重载， 用于处理指针 */
// 注意，如果不加const，则重载会在数组时发送冲突，即T(&a)[N] 和T * a发生冲突
template <typename T>
void print(const T *d){ // 如果此处的形参为 T * &d,则该函数不是重载,而是上一个模板函数的特例化
    print(*d);
}

/* 模板函数 ：上一个函数的重载,用于处理数组，1维或2维都可以使用 ，该模板函数包含类型形参和非类型形参*/
template <typename T, int N>
void print(T(&a)[N]){
    for(int i=0; i<N; i++){
        print(a[i]);
    }
}

/*特例化模板，用于处理特殊的字符串:注意，该函数是 void print(const T *d)的特例化，故不能写成 void print<char *>(const char * s) */
template <>
void print<char>(const char *a){
    cout << a ;
}

int main(void)
{
    int a = {10};
    const int *b = &a;
    int c[5] = {1, 2, 3, 4, 5};
    int d[2][3] = {1, 2, 3, 4, 5, 6};
    const char *e = "hello";
    print(a);
    cout << endl;
    print(b);
    cout << endl;
    print(c);
    cout << endl;
    print(d);
    cout << endl;
    print(e);
    cout << endl;
}
