/* 该文件主要测试特殊化模板类,包括部分特殊化和全特殊化 */
#include <iostream>
#include <string>
using namespace std;
// 一般模板类
template <typename T, typename V>
struct Pair{
    T first;
    V second;
    void show(){cout<<"normal"<<endl;};
};

// 部分特殊化模板类
template <typename T>
struct Pair<T, const char *>{
    T first;
    string second;
    void show(){cout<<"part char ptr 2"<<endl;};
};

// 注意这里数据的顺序，
template <typename T>
struct Pair<const char *, T>{
    string first;
    T second; // 为保证makePair正常工作，必须把T放在后面
    void show(){cout<<"part char ptr 1"<<endl;};
};

// 全特化模板类
template <>
struct Pair<const char *,const char *>
{
    string first;
    string second;
    void show(){cout<<"all char ptr"<<endl;};
};

// tip 用模板函数判断类型
template <typename T, typename U>
Pair<T,U> MakePair(T a, U b){
    Pair<T,U> p = {a, b};
    return p;
}

int main(void)
{
    MakePair("nihao",1).show();
    MakePair(1,"nihao").show();
    MakePair(1.1, 1.1).show();
    MakePair("nihao","wobuhao").show();
}

