#include <iostream>
#include <stack>
class TempClass{
    public:
    static int a ;
    TempClass::TempClass(char * name){
        a = a + 1;
    };
    TempClass::TempClass(){;};
    void init_a(){a = 1;};
    void display_a(){std::cout<<a<<std::endl;};
};

int main(void){
    TempClass j ;
    j.init_a();
    char one[] = "in ds";
    j = one;
    j.display_a();
    return 0;
}