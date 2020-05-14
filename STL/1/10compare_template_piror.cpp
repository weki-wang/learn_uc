#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
void my_add(int a, int b){
    int c = a + b;
    cout << "int fun called. result is " << c << endl;
};

template <typename T>
void my_add(T a, T b){
    T c = a + b;
    cout << "template fun called. result is " << c << endl;
};

template <>
void my_add<const string>(const string a, const string b){
    string c = a + b;
    cout << "string fun called. result is " << c.c_str() << endl;
};

template <>
void my_add<const char *>(const char *p1, const char *p2){
    char *p4 = new char[256] ;
    char *p3 = p4;
    for(int i = 0;*(p1+i) != '\0';i++,p3++)
        *p3 = *(p1+i);
    for(int j = 0;*(p2+j) != '\0';j++,p3++)
        *p3 = *(p2+j);
    *p3 = '\0'; // 空字符
    cout << "char ptr fun called. result is " << p4 << endl;
    delete(p4);
};

int main(void)
{
    my_add(3, 4);
    my_add(3.3, 4.4);
    const char *p1 = "hello";
    const char *p2 = " world";
    my_add(p1, p2);
}