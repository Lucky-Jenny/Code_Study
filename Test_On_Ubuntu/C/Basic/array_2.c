#include <stdio.h>

int main()
{
	int i=0, j=0;
	static char we[4][4]={{"abcd"}};
	//sizeof("what")=5  because it contains "/0"
	printf("sizeof(\"what\")=%ld\n",sizeof("what"));
	//In the way of snprintf(), we[][] should be &we[][]
	i=snprintf(&we[1][0],sizeof("what"),"what");	
	if(i<0) return 0;

	//If the length is beyond this line, th rest will write into next line.
	i=snprintf(&we[2][0],sizeof("whateew"),"whateew");
	if(i<0) return 0;

	printf("Print the Array.\n");
	//print the result of 2d-array
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{ printf("%c\t",we[i][j]);}
	printf("\n");
	}
}

