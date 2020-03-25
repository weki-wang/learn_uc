#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[], char* env[])
{
	int i ;
	char* p = NULL;
	putenv("MY_NAME=weki");
	p = getenv("MY_NAME");
	puts(p);
	setenv("MY_NAME","weki-wang",1);
	p = getenv("MY_NAME");
	puts(p);
}
