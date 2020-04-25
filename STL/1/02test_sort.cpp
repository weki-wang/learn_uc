/*该文件主要测试两种不同的排序 */
#include <iostream>

using namespace std;

void SortOne(int a[], int n){
    int num = 0;
    int num_n = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            num_n++;
            if(a[i]<a[j]){
                swap(a[i],a[j]);
                num++;
            }
        }
    }
    for(int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << "sort one loop : " << num_n << " and swap " << num << endl;
}
void SortTwo(int a[], int n){
    int num = 0;
    int num_n = 0;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            num_n++;
            if(a[i]>a[j]){
                swap(a[i],a[j]);
                num++;
            }
        }
    }
    for(int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    cout << "sort Two loop : " << num_n << " and swap " << num << endl;
}
int main(void)
{
    int a1[7] ={ 5, 8, 7, 3, 5, 6, 1};
    int a2[7] ={ 5, 8, 7, 3, 5, 6, 1};
    int b1[14] ={ 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1};
    int b2[14] ={ 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1};
    int c1[28] ={ 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1};
    int c2[28] ={ 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1, 5, 8, 7, 3, 5, 6, 1};
    SortOne(a1, 7);
    SortTwo(a2, 7);
    SortOne(b1, 14);
    SortTwo(b2, 14);
    SortOne(c1, 28);
    SortTwo(c2, 28);
}