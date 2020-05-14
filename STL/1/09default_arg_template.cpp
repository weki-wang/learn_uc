// 默认参数的模板类和模板函数
#include <iostream>
#include <cstring>
using namespace std;

template<typename T = int, int N = 10>
class MyArray{

    public:
        // 一般函数
        template<typename K>
        void fill(K start_value, int step){
            for(int i = 0; i < N ; i++, start_value += step){
                data[i] = start_value;
            }
        };
        // 模板函数-特例化
        template <>
        void fill<char *>(char * start_value,int size_num=N){
            for(int i = 0; i < N; i++){
                data[i] = start_value;
            }
        };

        template <>
        void fill<string>(string start_value, int size_num=N){
            for(int i = 0; i < N; i++){
                data[i] = start_value;
            }
        };

        const T& operator[](int index) const{
            return data[index];
        };

        T* Myfind(const T& find_data) const{
            T* result = NULL;
            for(int i = 0; i < N; i++){
                if(data[i] = find_data){
                    result = (data + i);
                    break;
                }
            }
            return result;
        };

        friend ostream operator<<(ostream& o, const MyArray& a){
            o << "The array value is:";
            for(int i = 0; i < N ; i++)
                o << a[i] << " ";
            o << endl;
        };

    private:
        T data[N];

};



int main(void)
{
    MyArray<> a;
    a.fill(1, 1);
    cout << a;
    int* tmepa = a.Myfind(2);
    cout << tmepa << " and value is " << *tmepa;

    MyArray<char> c;
    c.fill('c', 1);
    cout << c;
    MyArray<double, 5> d;
    d.fill(1.2, 3);
    cout << d;
    MyArray<char*,4> cptr;
    cptr.fill("nihao",4);
    cout << cptr;
    string temp("I'm a string");
    MyArray<string, 4> s;
    s.fill(temp, 4);
    cout << s;
    

}