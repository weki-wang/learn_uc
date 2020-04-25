/*该文件主要是模板函数template function的样例程序 */
#include <iostream>
#include <string>

using namespace std;

/*一般模板函数，包含的是类型形参T，
    还有非类型形参如(详情见06文件)
    templat <typename T,int N>
    void print(T(&a)[N]){
        ...
    }

*/
template <typename T>
void Sort(T a[], int n){
    for(int i=0; i<n; i++)
        for(int j=0; j<i; j++)
            if(a[i] < a[j])
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
    // 注意，此处使用的是string，如果使用是char *的类型，则使用函数模板时，a[i] < a[j]比较的是char 指针的地址大小
    // 如果仍想模板函数成立，必须声明特例化模板，见05special_template.cpp文件
    string as[4] = {"good", "morning", "dear", "friends"};
    Sort(ai, 6);
    PrintToScreen(ai, 6);
    Sort(ac, 5);
    PrintToScreen(ac, 5);
    Sort(ad, 4);
    PrintToScreen(ad, 4);
    Sort(as, 4);
    PrintToScreen(as, 4);
}