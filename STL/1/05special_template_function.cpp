/* 本程序主要测试特例化模板函数*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/* 模板函数*/
template <typename T>
bool LessThen(T const &a, T const &b){
    return a < b;
}

/*为处理char *类型的数据，需要将模板特例化,  const char * const & 的详细含义可见04文件*/
template <>
bool LessThen<const char *>(const char * const &a, const char * const &b){
    return (strcmp(a,b)<0);
}

/*一般模板函数 */
template <typename T>
void Sort(T a[], int n){
    for(int i=0; i<n; i++)
        for(int j=0; j<i; j++)
            if(LessThen(a[i], a[j]))
                swap(a[i], a[j]);
}

template <typename T>
void PrintToScreen(T a[], int n){
    for(int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
}
int main(void)
{
    int ai[6] = {8, 1, 6, 9, 3, 5};
    char ac[5] = {'a','e','i','o','u'};
    double ad[4] = {2.2, 3.3, 1.1, 7.7};
    const char *as[4] = {"good", "morning", "dear", "friends"};
    Sort(ai, 6);
    PrintToScreen(ai, 6);
    Sort(ac, 5);
    PrintToScreen(ac, 5);
    Sort(ad, 4);
    PrintToScreen(ad, 4);
    Sort(as, 4);
    PrintToScreen(as, 4);

}