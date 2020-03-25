#include "my_str.h"
void my_toupper(char *str){
  while(*str){
      if(*str>='a'&&*str<='z')
	*str += 'A'-'a';
      str++;
  }
}
