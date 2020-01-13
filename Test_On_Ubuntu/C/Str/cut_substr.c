#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TL 1

char *delchar(char str[], char *substr)
{
	if(str == NULL) { return NULL; }
		int i=0, j=0;
		char q[60], p[80];
		strcpy(p, str);
		while(p[i]){
		    if(strncmp(p+i,substr,sizeof(substr)) == 0)
			{ i += sizeof(substr); }
			else
			{ q[j++] = p[i++]; }
		}
		q[j] = '\0';
		char *res;
		res = (char *)malloc(sizeof(char)*50);
		sprintf(res,q);
		printf("%s", res);
		return res;
}

#if TL
// #define  LX(format,...) printf("This means str=1.\n%s\n", ##__VA_ARGS__)
#define LX(info) printf("%s\n",info)
#else
#define LX(info) printf("%s", delchar(info,"/dev/console"))
#endif

int main()
{
	char p[] = "echo Do u like apple? >/dev/console";
	char q[] = ">/dev/console";
	LX(p);
	printf("%s\n", delchar(p, q));
	printf("%d\n", sizeof(q));
}

