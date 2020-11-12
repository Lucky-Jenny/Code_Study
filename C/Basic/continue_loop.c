/*
 2020.11.12 ---> I can,t believe that I just know this point, shit......
*/
#include <stdio.h>

int main()
{
	int i = 0;

	for(i = 0; i < 10; i++){
		// continue--> end this loop, start with next loop
		if(i == 3)	continue;
		printf("%d ", i);
	}
	printf("\n");
}
