#include <stdio.h>
#include <string.h>

void single_quote()
{
	char addr[] = "test ab'cd";
	char str[128] = {0}, rst[128] = {0};
	char *p = NULL, *q = NULL;

	snprintf(str, sizeof(str), "%.31s", addr);

	p = addr;
	q = rst;
	int i = 0;
	for(;*p != '\0'; p++){
		if(*p == '\''){
			*q++ = '\'';
			*q++ = '\\';
			*q++ = '\'';
		}
		*q++ = *p;
	}
	printf("[str] %s\tlen=%ld\n", str, strlen(str));
	printf("[rst] %s\tlen=%ld\n", rst, strlen(rst));	
}

int main()
{
	single_quote();
	return 0;
}

