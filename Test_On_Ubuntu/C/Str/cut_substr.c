#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TL 0

char *delchar(char str[], char *substr)
{
	if(str == NULL) { return NULL; }
		int i=0, j=0;
		char q[60], p[80];
		strcpy(p, str);
		while(p[i]){	
		    if(strncmp(p+i,substr,strlen(substr)) == 0)
			{ i += strlen(substr); }
			else
			{ q[j] = p[i]; j++; i++; }
		}
		// NOTE: strlen() != sizeof()
		//printf("strlen(sub)=%ld\tsizeof(sub)=%ld\n", strlen(substr), sizeof(substr));
		q[j] = '\0';
		char *res;
		res = (char *)malloc(sizeof(char)*50);
		strncpy(res, q, strlen(q));
		return res;
}

#if TL
// #define  LX(format,...) printf("This means str=1.\n%s\n", ##__VA_ARGS__)
#define LX(info) printf("%s\n",info)
#else
#define LX(info) printf("deal in #ifdef:\n%s\n", delchar(info,"/dev/console"))
#endif

int main()
{
	char p[] = "echo Do u like apple? >/dev/console";
	char q[] = ">/dev/console";
	printf("Original string:\n%s\n", p);
	LX(p);
	printf("deal in main:\n%s\n", delchar(p, q));
}

