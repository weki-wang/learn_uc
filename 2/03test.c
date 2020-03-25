#include <stdio.h>
#pragma pack(4)
typedef struct A{
	char a;
	double b;
	char c;
}A;

typedef struct B{
	char a;
	double b;
	char c;
}__attribute__((aligned(16))) SB;


int main(void)
{
	printf("%ld\n",sizeof(A));
	printf("%ld\n",sizeof(SB));
	return 0;
}
