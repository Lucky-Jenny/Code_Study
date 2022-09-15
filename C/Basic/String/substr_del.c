#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TL 1	// a switch of printf in #define.

char *delstr(char str[], char *substr)
{
	if(str == NULL) { return NULL; }
	int i = 0, j = 0;
	char q[200], p[200];
	char *res;
	strcpy(p, str);
	while(p[i]) {	
	    if(strncmp(p+i, substr, strlen(substr)) == 0)
			i += strlen(substr);
		else
			q[j++] = p[i++];
	}
	// NOTE: strlen() != sizeof()
	q[j] = '\0';
	res = q;
	// q is also a pointer, but it only return address.
	// for  return the string, u need to use a new pointer to point to q.
	return res;
}

#if TL
// #define  LX(format,...) printf("This means str=1.\n%s\n", ##__VA_ARGS__)
#define LX(info)
#else
#define LX(info) printf("process in #ifdef:\n%s\n", delstr(info,"/dev/console"))
#endif

int main()
{
	char p[] = "Do u like this big apple? Yes I do.";
	char q[] = "this big ";
	printf("%s\n%s\n", p, q);
	//LX(p);
	printf("==>\n%s\n", delstr(p, q));
}

