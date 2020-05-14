#include <iostream>
using namespace std;

template <typename T>
class MyClass{
    private:
        static int i_num;

    public :
        MyClass(){
            i_num++;
        };

        ~MyClass(){
            --i_num;
        };

        void display(){
            cout << i_num << endl;
        };
};
template<typename T>
int MyClass<T>::i_num = 0;

int main(void)
{
    MyClass<int> a;
    a.display();
    MyClass<double> b;
    b.display();
    MyClass<double> c;
    c.display();

    return 0;
}