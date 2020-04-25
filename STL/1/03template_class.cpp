#include <iostream>
#define MAX_STACK_NUM 100
using namespace std;
template <typename T>
class MyStack{
    private:
        T s[MAX_STACK_NUM];
        int cnt;

    public:
        MyStack():cnt(0){}; /* construct*/
        void push(const T a){s[cnt++]=a;};
        void pop(){if(cnt>0){--cnt;}};
        int size(){return cnt;};

};

int main(void)
{
    MyStack<int> a;
    MyStack<const char*> b;
    a.push(1);
    a.push(2);
    a.push(3);
    a.push(4);
    b.push("hello");
    b.push("world");
    cout << "a size is " << a.size() << endl;
    cout << "b size is " << b.size() << endl;

    return 0;
}