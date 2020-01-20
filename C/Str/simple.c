#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *test="2";
	//int x = atoi(test);
	switch(atoi(test))
	{
		case 1:
			printf("1\n");
		case 2:
			printf("2\n");break;
		case 3:
			printf("3\n");break;
		default:
			break;
	}
	int i = strcmp("abc","abcde");
	int j = strncmp("abc","abcde",3);
	printf("Compare \"abc\" with \"abcde\"\n");
	printf("strcmp:  %d\nstrncmp: %d\n",i,j);
	if(!j) { printf(" !j is true.\n"); } 

}
