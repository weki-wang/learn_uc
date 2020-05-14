#include <iostream>

using namespace std;

template <typename T, int N>
class MyArray{

    public:
        void fillArray(T start_value, int step){
            for(int i = 0; i < N; i++, start_value += step){
                a[i] = start_value;
            }
        };

        T& operator[](int index){
            if(index < N)
                return a[index];
        };

        // 该函数相当于上一个函数的重载,隐含的意思是,在形参里面添加了一个 const this指针
        const T& operator[](int index) const{
            if(index < N)
                return a[index];
        };

        /*
        friend ostream& operator<<(ostream& o, const MyArray& a){
            o << "[";
            for(int i = 0; i < N; i++){
                o << a[i] << " ";
            }
            o << "] \n";
            return o;
        };
        */
        // 如果在class外面定义函数,友元函数模板
        template <typename K, int M>
        friend ostream& operator<<(ostream& o, const MyArray<K,M>& a);
    private :
        T a[N];
};
template <typename K, int M>
ostream& operator<<(ostream& o, const MyArray<K,M>& a){
    o << "[";
    for(int i = 0; i < M; i++){
        o << a[i] << " ";
    }
    o << "] \n";
    return o;    
};


int main(void)
{
    MyArray<int, 5> a;
    a.fillArray(2 , 2);
    cout << a ;
    return 0;
}