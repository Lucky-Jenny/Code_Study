#include <stdio.h>
#include <stdlib.h>

#define TL 0

#if TL
#define LX(format,...) printf("This means str=1.\n%s\n", ##__VA_ARGS__)
#else
#define LX(format,...) printf(format, ##__VA_ARGS__)
#endif

int main()
{
	int m = 0;
	char *p ="apple";
	while(1){
		LX("asdfg:%s\n", p);
		sleep(2);
	}
}
// This is backup for add a switch on aws module.
char * delchar(char *str, char sub)
{
	if(str == NULL) { return NULL; }
	char *head = str;
	char *p = str;
	while(*p++){
		if(*p != sub)	{ *str++ = *p; }
	}
	*str = '\0';
	return head;
}

